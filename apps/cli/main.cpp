#include "pseries/device_selection.hpp"
#include "pseries/platform/pci_discovery.hpp"

#include <iomanip>
#include <iostream>
#include <string_view>

namespace {

const wchar_t* model_name(std::uint16_t device_id) {
    switch (device_id) {
    case 0x1B07:
        return L"P102-100";
    case 0x1B87:
        return L"P104-100";
    case 0x1BC7:
        return L"P104-101";
    case 0x1C07:
        return L"P106-100";
    case 0x1C09:
        return L"P106-090";
    default:
        return L"Unknown P-series device";
    }
}

void print_help() {
    std::wcout
        << L"PSeriesUnlock-Native (development build)\n"
        << L"Independent native implementation; not a wrapper around the reference executable.\n\n"
        << L"Usage:\n"
        << L"  PSeriesUnlock-Native.exe help\n"
        << L"  PSeriesUnlock-Native.exe list\n\n"
        << L"Implemented commands:\n"
        << L"  list    Read-only inventory of present PCI devices and known P-series GPUs.\n\n"
        << L"Hardware modification, driver loading, unlock, recovery, and CUDA verification\n"
        << L"are not implemented in this build.\n";
}

int list_devices() {
    const auto discovered = pseries::platform::enumerate_present_pci_devices();
    if (!discovered.has_value()) {
        std::cerr << "PCI discovery failed: " << discovered.error().message << '\n';
        return 1;
    }

    std::size_t supported_count = 0;
    for (const auto& device : discovered.get()) {
        if (pseries::is_known_p_series_gpu(device.identity)) {
            ++supported_count;
        }
    }

    std::wcout
        << L"Read-only PCI inventory. No driver is loaded and no hardware is modified.\n"
        << L"PCI devices scanned: " << discovered.get().size() << L"\n"
        << L"Known P-series GPUs: " << supported_count << L"\n";

    for (const auto& device : discovered.get()) {
        if (!pseries::is_known_p_series_gpu(device.identity)) {
            continue;
        }

        std::wcout << L"\n" << model_name(device.identity.device_id)
                   << L"  [" << std::hex << std::uppercase << std::setfill(L'0')
                   << std::setw(4) << device.identity.vendor_id << L":"
                   << std::setw(4) << device.identity.device_id << L"]"
                   << std::dec << L"\n";
        std::wcout << L"  Instance: " << device.instance_id << L"\n";
        if (!device.description.empty()) {
            std::wcout << L"  Name: " << device.description << L"\n";
        }
        if (!device.location.empty()) {
            std::wcout << L"  Windows location: " << device.location << L"\n";
        }
        if (device.identity.subsystem_vendor_id && device.identity.subsystem_device_id) {
            std::wcout << L"  Subsystem: "
                       << std::hex << std::uppercase << std::setfill(L'0')
                       << std::setw(4) << *device.identity.subsystem_vendor_id << L":"
                       << std::setw(4) << *device.identity.subsystem_device_id
                       << std::dec << L"\n";
        }
    }

    if (supported_count == 0) {
        std::wcout << L"No supported P-series GPU is currently present.\n";
    }
    return 0;
}

} // namespace

int wmain(int argc, wchar_t* argv[]) {
    if (argc == 1 || (argc == 2 && std::wstring_view(argv[1]) == L"help")) {
        print_help();
        return 0;
    }
    if (argc == 2 && std::wstring_view(argv[1]) == L"list") {
        return list_devices();
    }

    std::wcerr << L"Unsupported command or arguments. Run `PSeriesUnlock-Native.exe help`.\n";
    return 2;
}
