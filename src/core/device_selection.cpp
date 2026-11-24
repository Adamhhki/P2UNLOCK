#include "pseries/device_selection.hpp"

namespace pseries {

namespace {

constexpr std::uint16_t nvidia_vendor_id = 0x10DE;

constexpr bool is_known_device_id(std::uint16_t device_id) noexcept {
    switch (device_id) {
    case 0x1B07: // P102-100
    case 0x1B87: // P104-100
    case 0x1BC7: // P104-101
    case 0x1C07: // P106-100
    case 0x1C09: // P106-090
        return true;
    default:
        return false;
    }
}

} // namespace

bool is_known_p_series_gpu(const HardwareIdentity& identity) noexcept {
    return identity.vendor_id == nvidia_vendor_id && is_known_device_id(identity.device_id);
}

Result<HardwareIdentity> select_unique_p_series_gpu(std::span<const HardwareIdentity> devices) {
    const HardwareIdentity* candidate = nullptr;

    for (const auto& device : devices) {
        if (!is_known_p_series_gpu(device)) {
            continue;
        }
        if (candidate != nullptr) {
            return Result<HardwareIdentity>{{Error{
                ErrorCode::unsupported,
                "Multiple known P-series GPUs found; refusing ambiguous selection"}}};
        }
        candidate = &device;
    }

    if (candidate == nullptr) {
        return Result<HardwareIdentity>{{Error{
            ErrorCode::hardware_not_found,
            "No known P-series GPU found"}}};
    }
    if (!candidate->bdf || !candidate->bdf->is_valid()) {
        return Result<HardwareIdentity>{{Error{
            ErrorCode::unsupported,
            "P-series GPU has no valid PCI address"}}};
    }

    return Result<HardwareIdentity>{{*candidate}};
}

} // namespace pseries
