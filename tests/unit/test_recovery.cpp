#include "pseries/recovery.hpp"

#include <cstring>
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
    pseries::RecoveryValidationOptions options{};

    auto empty = pseries::parse_recovery_state({}, options);
    expect(empty.has_value(), "empty state is representable");
    expect(empty.has_value() && empty.get() == pseries::RecoveryStateStatus::none,
           "empty state means none");

    std::uint8_t short_record[] = {1, 2, 3};
    auto short_result = pseries::parse_recovery_state(short_record, options);
    expect(!short_result.has_value(), "short recovery record rejected");

    pseries::RecoveryRecordHeader header{};
    header.magic = 0x31534e50u;
    header.version = 5u;
    header.payload_size = sizeof(header);
    std::uint8_t record[sizeof(header)];
    std::memcpy(record, &header, sizeof(header));

    auto result = pseries::parse_recovery_state(record, options);
    expect(result.has_value(), "valid synthetic recovery header accepted");
    expect(result.has_value() && result.get() == pseries::RecoveryStateStatus::pending,
           "pending state returned");

    header.magic = 0u;
    std::memcpy(record, &header, sizeof(header));
    auto mismatch = pseries::parse_recovery_state(record, options);
    expect(!mismatch.has_value(), "magic mismatch rejected");

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
