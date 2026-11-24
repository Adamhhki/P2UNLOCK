#pragma once

#include "pseries/types.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <span>
#include <string>

namespace pseries {

enum class RecoveryStateStatus : std::uint8_t {
    none,
    pending,
    recovering,
    recovered,
    blocked,
};

struct RecoveryRecordHeader {
    std::uint32_t magic{};
    std::uint32_t version{};
    std::uint32_t payload_size{};
};

struct RecoveryValidationOptions {
    bool allow_unknown_fields{false};
};

Result<RecoveryStateStatus> parse_recovery_state(
    std::span<const std::uint8_t> bytes,
    const RecoveryValidationOptions& options) noexcept;

} // namespace pseries
