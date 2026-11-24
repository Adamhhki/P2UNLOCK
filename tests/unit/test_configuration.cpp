#include "pseries/configuration.hpp"

#include <cstdlib>
#include <iostream>

namespace {
int failures = 0;
void expect(bool condition, const char* name) {
    if (!condition) {
        std::cerr << "FAILED: " << name << '\n';
        ++failures;
    }
}
} // namespace

int main() {
    pseries::ServiceConfiguration valid;
    const auto valid_result = pseries::validate_service_configuration(valid);
    expect(valid_result.has_value(), "default configuration is valid");

    pseries::ServiceConfiguration unsupported;
    unsupported.schema_version = 99u;
    const auto unsupported_result = pseries::validate_service_configuration(unsupported);
    expect(!unsupported_result.has_value(), "unsupported schema rejected");
    expect(unsupported_result.error().code == pseries::ErrorCode::invalid_configuration,
           "unsupported schema error code");

    const auto parsed = pseries::parse_service_configuration(
        "schema_version=1\nhardware_modifications=disabled\n");
    expect(parsed.has_value(), "text configuration parsed");

    const auto unknown = pseries::parse_service_configuration(
        "schema_version=1\nhardware_modifications=disabled\nfuture_option=yes\n");
    expect(!unknown.has_value(), "unknown key rejected");

    const auto missing = pseries::parse_service_configuration("schema_version=1\n");
    expect(!missing.has_value(), "missing required key rejected");
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
