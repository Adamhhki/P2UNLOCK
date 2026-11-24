#include "pseries/platform/seavo_backend.hpp"

#include "pseries/seavo_protocol.hpp"

#include <array>
#include <cstddef>
#include <cstring>
#include <string>

namespace pseries::platform {

namespace {

constexpr wchar_t seavo_device_path[] = L"\\\\.\\SvIoCtrl_1_0_0";

Error win32_error(const char* operation, DWORD error) {
    return Error{
        ErrorCode::service_error,
        std::string(operation) + " failed with Win32 error " + std::to_string(error)};
}

Error validate_access(std::uint64_t address, std::uint32_t width) {
    if (!seavo::is_supported_physical_width(width)) {
        return Error{ErrorCode::invalid_argument, "Physical access width must be 1, 2, or 4 bytes"};
    }
    if (!seavo::is_aligned_physical_access(address, width)) {
        return Error{ErrorCode::invalid_argument, "Physical access address is not naturally aligned"};
    }
    return Error{};
}

} // namespace

SeavoBackend::SeavoBackend(HANDLE device) noexcept
    : device_(device) {
}

SeavoBackend::~SeavoBackend() {
    if (device_ != INVALID_HANDLE_VALUE) {
        CloseHandle(device_);
    }
}

Result<std::unique_ptr<SeavoBackend>> SeavoBackend::open() {
    const auto device = CreateFileW(
        seavo_device_path,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
    if (device == INVALID_HANDLE_VALUE) {
        return Result<std::unique_ptr<SeavoBackend>>{{win32_error("Open Seavo device", GetLastError())}};
    }

    return Result<std::unique_ptr<SeavoBackend>>{std::unique_ptr<SeavoBackend>(
        new SeavoBackend(device))};
}

Result<std::uint32_t> SeavoBackend::read_physical(
    std::uint64_t address,
    std::uint32_t width) const {
    const auto validation = validate_access(address, width);
    if (validation.code != ErrorCode::none) {
        return Result<std::uint32_t>{{validation}};
    }

    seavo::PhysicalAccessHeader request{address, width, 1};
    std::array<std::byte, sizeof(std::uint32_t)> output{};
    DWORD bytes_returned = 0;
    if (!DeviceIoControl(
            device_,
            seavo::physical_read_ioctl,
            &request,
            sizeof(request),
            output.data(),
            width,
            &bytes_returned,
            nullptr)) {
        return Result<std::uint32_t>{{win32_error("Read physical memory", GetLastError())}};
    }
    if (bytes_returned != width) {
        return Result<std::uint32_t>{{Error{
            ErrorCode::service_error,
            "Seavo physical read returned an unexpected byte count"}}};
    }

    std::uint32_t value = 0;
    std::memcpy(&value, output.data(), width);
    return Result<std::uint32_t>{value};
}

Result<void> SeavoBackend::write_physical(
    std::uint64_t address,
    std::uint32_t width,
    std::uint32_t value) const {
    const auto validation = validate_access(address, width);
    if (validation.code != ErrorCode::none) {
        return Result<void>{{validation}};
    }

    std::array<std::byte, seavo::physical_access_header_size + sizeof(value)> input{};
    const seavo::PhysicalAccessHeader request{address, width, 1};
    std::memcpy(input.data(), &request, sizeof(request));
    std::memcpy(input.data() + sizeof(request), &value, width);

    DWORD bytes_returned = 0;
    if (!DeviceIoControl(
            device_,
            seavo::physical_write_ioctl,
            input.data(),
            static_cast<DWORD>(sizeof(request) + width),
            nullptr,
            0,
            &bytes_returned,
            nullptr)) {
        return Result<void>{{win32_error("Write physical memory", GetLastError())}};
    }
    if (bytes_returned != 0) {
        return Result<void>{{Error{
            ErrorCode::service_error,
            "Seavo physical write returned an unexpected byte count"}}};
    }

    return Result<void>{};
}

} // namespace pseries::platform
