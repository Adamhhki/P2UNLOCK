#include "pseries/device_selection.hpp"

#include <array>
#include <cstdlib>
#include <iostream>

namespace {

int failures = 0;

void expect(bool condition, const char* test_name) {
    if (!condition) {
        std::cerr << "FAILED: " << test_name << '\n';
        ++failures;
    }
}

pseries::HardwareIdentity identity(
    std::uint16_t vendor_id,
    std::uint16_t device_id,
    std::uint8_t device,
    bool include_bdf = true) {
    pseries::HardwareIdentity result;
    result.vendor_id = vendor_id;
    result.device_id = device_id;
    if (include_bdf) {
        result.bdf = pseries::PciBdf{0, 1, device, 0};
    }
    return result;
}

} // namespace

int main() {
    const auto p104 = identity(0x10DE, 0x1B87, 0);
    const auto unrelated_nvidia = identity(0x10DE, 0x1B80, 1);
    const auto other_vendor = identity(0x1002, 0x1B87, 2);
    const std::array devices{unrelated_nvidia, other_vendor, p104};

    expect(pseries::is_known_p_series_gpu(p104), "recognize P104-100 by vendor and device ID");
    expect(!pseries::is_known_p_series_gpu(unrelated_nvidia), "reject unrelated NVIDIA GPU");
    expect(!pseries::is_known_p_series_gpu(other_vendor), "reject matching device ID from another vendor");

    const auto selected = pseries::select_unique_p_series_gpu(devices);
    expect(selected.has_value(), "automatically select the single known P-series GPU");
    if (selected.has_value()) {
        expect(selected.get().device_id == 0x1B87, "return selected GPU identity");
        expect(
            selected.get().bdf &&
                selected.get().bdf->domain == 0 &&
                selected.get().bdf->bus == 1 &&
                selected.get().bdf->device == 0 &&
                selected.get().bdf->function == 0,
            "retain selected PCI address");
    }

    const std::array no_candidates{unrelated_nvidia, other_vendor};
    const auto not_found = pseries::select_unique_p_series_gpu(no_candidates);
    expect(!not_found.has_value(), "report no known P-series GPU");
    if (!not_found.has_value()) {
        expect(not_found.error().code == pseries::ErrorCode::hardware_not_found, "use not-found error code");
    }

    const std::array ambiguous{p104, identity(0x10DE, 0x1C07, 3)};
    const auto multiple = pseries::select_unique_p_series_gpu(ambiguous);
    expect(!multiple.has_value(), "refuse ambiguous multiple-GPU selection");
    if (!multiple.has_value()) {
        expect(multiple.error().code == pseries::ErrorCode::unsupported, "use unsupported error code");
    }

    const std::array missing_address{identity(0x10DE, 0x1B87, 0, false)};
    const auto no_address = pseries::select_unique_p_series_gpu(missing_address);
    expect(!no_address.has_value(), "refuse selection without a valid PCI address");
    if (!no_address.has_value()) {
        expect(no_address.error().code == pseries::ErrorCode::unsupported, "use unsupported error code");
    }

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
