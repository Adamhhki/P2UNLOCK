#include "pseries/seavo_protocol.hpp"

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
    using pseries::seavo::is_aligned_physical_access;
    using pseries::seavo::is_supported_physical_width;

    expect(is_supported_physical_width(1), "accept byte access");
    expect(is_supported_physical_width(2), "accept word access");
    expect(is_supported_physical_width(4), "accept dword access");
    expect(!is_supported_physical_width(8), "reject qword access");
    expect(is_aligned_physical_access(0x1000, 4), "accept aligned dword address");
    expect(!is_aligned_physical_access(0x1002, 4), "reject misaligned dword address");
    expect(!is_aligned_physical_access(0x1001, 0), "reject invalid width");

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
