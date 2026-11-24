#include "pseries/pci_identity.hpp"

#include <cstdlib>
#include <iostream>
#include <string_view>

namespace {

int failures = 0;

void expect(bool condition, const char* test_name) {
    if (!condition) {
        std::cerr << "FAILED: " << test_name << '\n';
        ++failures;
    }
}

} // namespace

int main() {
    const auto p104 = pseries::parse_pci_hardware_id(
        "PCI\\VEN_10DE&DEV_1B87&SUBSYS_1B8710DE&REV_A1");
    expect(p104.has_value(), "parse a complete PCI hardware ID");
    if (p104.has_value()) {
        expect(p104.get().vendor_id == 0x10DE, "parse vendor ID");
        expect(p104.get().device_id == 0x1B87, "parse device ID");
        expect(
            p104.get().subsystem_device_id == 0x1B87 &&
                p104.get().subsystem_vendor_id == 0x10DE,
            "split subsystem device and vendor fields");
    }

    const auto lowercase = pseries::parse_pci_hardware_id("pci\\ven_10de&dev_1c09");
    expect(lowercase.has_value(), "parse fields case-insensitively without subsystem");
    if (lowercase.has_value()) {
        expect(
            !lowercase.get().subsystem_vendor_id && !lowercase.get().subsystem_device_id,
            "leave missing subsystem fields unset");
    }

    const auto malformed = pseries::parse_pci_hardware_id("PCI\\VEN_10DE&DEV_GGGG");
    expect(!malformed.has_value(), "reject malformed hexadecimal device ID");
    if (!malformed.has_value()) {
        expect(
            malformed.error().code == pseries::ErrorCode::invalid_argument,
            "report malformed hardware ID as invalid input");
    }

    const auto non_pci = pseries::parse_pci_hardware_id("USB\\VID_10DE&PID_1B87");
    expect(!non_pci.has_value(), "reject non-PCI device IDs");

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
