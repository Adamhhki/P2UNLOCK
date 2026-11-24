#include "pseries/auto_peg_support.hpp"

#include "pseries/device_selection.hpp"

namespace pseries {

namespace {

constexpr std::uint16_t intel_vendor_id = 0x8086;
constexpr std::uint16_t p104_100_device_id = 0x1B87;
constexpr std::uint32_t group_signature_mask = 0x7FFFFFFF;

bool is_direct_cpu_peg_port(const HardwareIdentity& identity) noexcept {
    return identity.bdf &&
        identity.bdf->domain == 0 &&
        identity.bdf->bus == 0 &&
        identity.bdf->device == 1 &&
        identity.bdf->function == 0;
}

} // namespace

Result<AutoPegPathInfo> classify_auto_peg_path(
    const HardwareIdentity& gpu,
    const HardwareIdentity& upstream) {
    if (!is_known_p_series_gpu(gpu)) {
        return Result<AutoPegPathInfo>{{Error{
            ErrorCode::unsupported,
            "GPU is not in the known P-series device list"}}};
    }

    if (upstream.vendor_id != intel_vendor_id || !is_direct_cpu_peg_port(upstream)) {
        return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::standard, 0}}};
    }

    switch (upstream.device_id) {
    case 0x0C01:
        return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::private_peg_candidate, 0x6EF8AA78}}};
    case 0x1901:
        return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::private_peg_candidate, 0x1D788838}}};
    case 0x1601:
        if (gpu.device_id == p104_100_device_id) {
            return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::private_peg_candidate, 0x2AFAD924}}};
        }
        return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::standard, 0}}};
    case 0x9A01:
        if (gpu.device_id == p104_100_device_id) {
            return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::gen2_only, 0}}};
        }
        return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::standard, 0}}};
    default:
        return Result<AutoPegPathInfo>{{AutoPegPathInfo{AutoPegPath::standard, 0}}};
    }
}

bool low31_group_signatures_match(
    std::span<const std::uint32_t> group_registers,
    std::uint32_t expected_signature) noexcept {
    if (group_registers.size() != 8 || (expected_signature & ~group_signature_mask) != 0) {
        return false;
    }

    for (const auto value : group_registers) {
        if ((value & group_signature_mask) != expected_signature) {
            return false;
        }
    }
    return true;
}

} // namespace pseries
