#include "pseries/recovery.hpp"

#include <cstring>

namespace pseries {

Result<RecoveryStateStatus> parse_recovery_state(
    std::span<const std::uint8_t> bytes,
    const RecoveryValidationOptions& options) noexcept {
    if (bytes.empty()) {
        return Result<RecoveryStateStatus>{{RecoveryStateStatus::none}};
    }
    if (bytes.size() < sizeof(RecoveryRecordHeader)) {
        return Result<RecoveryStateStatus>{{Error{
            ErrorCode::invalid_recovery_state,
            "Recovery record is shorter than its header"}}};
    }

    RecoveryRecordHeader header{};
    std::memcpy(&header, bytes.data(), sizeof(header));
    if (header.magic != 0x31534e50u) {
        return Result<RecoveryStateStatus>{{Error{
            ErrorCode::invalid_recovery_state,
            "Recovery record magic mismatch"}}};
    }
    if (header.version < 1u || header.version > 5u) {
        return Result<RecoveryStateStatus>{{Error{
            ErrorCode::invalid_recovery_state,
            "Unsupported recovery schema"}}};
    }
    if (header.payload_size != bytes.size()) {
        return Result<RecoveryStateStatus>{{Error{
            ErrorCode::invalid_recovery_state,
            "Recovery payload size mismatch"}}};
    }
    if (options.allow_unknown_fields) {
        // Unknown fields are only ignored if a future migration explicitly enables it.
    }

    return Result<RecoveryStateStatus>{{RecoveryStateStatus::pending}};
}

} // namespace pseries
