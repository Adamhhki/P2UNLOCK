#include "pseries/types.hpp"

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

} // namespace

int main() {
    const auto bdf = pseries::parse_pci_bdf("0000:01:00.0");
    expect(bdf.has_value(), "valid PCI BDF");
    expect(bdf.has_value() && bdf.get().domain == 0, "BDF domain");
    expect(bdf.has_value() && bdf.get().bus == 1, "BDF bus");
    expect(bdf.has_value() && bdf.get().device == 0, "BDF device");
    expect(bdf.has_value() && bdf.get().function == 0, "BDF function");

    for (const char* invalid : {
        "0001:02:03",
        "0001x02:03.0",
        "0001:01:20.0",
        "0001:01:00.8",
        "0001:GG:00.0"}) {
        expect(!pseries::parse_pci_bdf(invalid).has_value(), "invalid PCI BDF");
    }
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
