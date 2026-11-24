#pragma once

#include "pseries/types.hpp"

#include <cstdint>
#include <span>

namespace pseries {

enum class AutoPegPath : std::uint8_t {
    standard,
    // A profile candidate only; live layout checks are still required before any write.
    private_peg_candidate,
    gen2_only,
};

struct AutoPegPathInfo {
    AutoPegPath path{AutoPegPath::standard};
    std::uint32_t expected_group_signature{};
};

[[nodiscard]] Result<AutoPegPathInfo> classify_auto_peg_path(
    const HardwareIdentity& gpu,
    const HardwareIdentity& upstream);

// Checks only the invariant low 31 signature bits; it does not validate active-group layout.
[[nodiscard]] bool low31_group_signatures_match(
    std::span<const std::uint32_t> group_registers,
    std::uint32_t expected_signature) noexcept;

} // namespace pseries
