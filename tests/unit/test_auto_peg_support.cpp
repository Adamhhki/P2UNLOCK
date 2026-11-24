#include "pseries/auto_peg_support.hpp"

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
    std::uint8_t bus,
    std::uint8_t device,
    std::uint8_t function) {
    pseries::HardwareIdentity result;
    result.vendor_id = vendor_id;
    result.device_id = device_id;
    result.bdf = pseries::PciBdf{0, bus, device, function};
    return result;
}

} // namespace

int main() {
    using pseries::AutoPegPath;

    const auto p104 = identity(0x10DE, 0x1B87, 1, 0, 0);
    const auto p102 = identity(0x10DE, 0x1B07, 1, 0, 0);
    const auto p104_101 = identity(0x10DE, 0x1BC7, 1, 0, 0);
    const auto p106_100 = identity(0x10DE, 0x1C07, 1, 0, 0);
    const auto p106_090 = identity(0x10DE, 0x1C09, 1, 0, 0);
    const auto haswell = identity(0x8086, 0x0C01, 0, 1, 0);
    const auto skylake = identity(0x8086, 0x1901, 0, 1, 0);
    const auto broadwell = identity(0x8086, 0x1601, 0, 1, 0);
    const auto hm570 = identity(0x8086, 0x9A01, 0, 1, 0);
    const auto h61 = identity(0x8086, 0x0151, 0, 1, 0);

    const auto haswell_path = pseries::classify_auto_peg_path(p104, haswell);
    expect(
        haswell_path.has_value() &&
            haswell_path.get().path == AutoPegPath::private_peg_candidate &&
            haswell_path.get().expected_group_signature == 0x6EF8AA78,
        "identify the documented Haswell PEG profile");

    const auto skylake_path = pseries::classify_auto_peg_path(p106_100, skylake);
    expect(
        skylake_path.has_value() &&
            skylake_path.get().path == AutoPegPath::private_peg_candidate &&
            skylake_path.get().expected_group_signature == 0x1D788838,
        "identify the documented Skylake PEG profile");
    const auto skylake_p104_101 = pseries::classify_auto_peg_path(p104_101, skylake);
    const auto haswell_p106_090 = pseries::classify_auto_peg_path(p106_090, haswell);
    expect(
        skylake_p104_101.has_value() &&
            skylake_p104_101.get().path == AutoPegPath::private_peg_candidate,
        "recognize P104-101 on the documented Intel 1901 path");
    expect(
        haswell_p106_090.has_value() &&
            haswell_p106_090.get().path == AutoPegPath::private_peg_candidate,
        "recognize P106-090 on the documented Intel 0C01 path");

    const auto broadwell_path = pseries::classify_auto_peg_path(p104, broadwell);
    expect(
        broadwell_path.has_value() &&
            broadwell_path.get().path == AutoPegPath::private_peg_candidate &&
            broadwell_path.get().expected_group_signature == 0x2AFAD924,
        "identify Broadwell PEG only for P104-100");
    const auto broadwell_p102 = pseries::classify_auto_peg_path(p102, broadwell);
    expect(
        broadwell_p102.has_value() &&
            broadwell_p102.get().path == AutoPegPath::standard,
        "keep P102 on standard path for Broadwell");
    const auto broadwell_p106 = pseries::classify_auto_peg_path(p106_100, broadwell);
    expect(
        broadwell_p106.has_value() &&
            broadwell_p106.get().path == AutoPegPath::standard,
        "keep non-P104 devices on standard path for Broadwell");

    const auto gen2_only = pseries::classify_auto_peg_path(p104, hm570);
    expect(
        gen2_only.has_value() && gen2_only.get().path == AutoPegPath::gen2_only,
        "classify the documented HM570 route as Gen2-only");
    const auto h61_path = pseries::classify_auto_peg_path(p104, h61);
    expect(
        h61_path.has_value() && h61_path.get().path == AutoPegPath::standard,
        "do not apply private PEG profile to H61");

    const auto wrong_peg_port = identity(0x8086, 0x1901, 0, 2, 0);
    const auto wrong_port_path = pseries::classify_auto_peg_path(p104, wrong_peg_port);
    expect(
        wrong_port_path.has_value() &&
            wrong_port_path.get().path == AutoPegPath::standard,
        "require the direct CPU PEG port BDF");

    const std::array<std::uint32_t, 8> groups{
        0x6EF8AA78, 0xEEF8AA78, 0x6EF8AA78, 0xEEF8AA78,
        0x6EF8AA78, 0xEEF8AA78, 0x6EF8AA78, 0xEEF8AA78};
    expect(
        pseries::low31_group_signatures_match(groups, 0x6EF8AA78),
        "match the documented low-31-bit group signature");
    auto invalid_groups = groups;
    invalid_groups[4] ^= 0x100;
    expect(
        !pseries::low31_group_signatures_match(invalid_groups, 0x6EF8AA78),
        "reject an unexpected group signature");
    expect(
        !pseries::low31_group_signatures_match(
            std::span<const std::uint32_t>(groups.data(), groups.size() - 1), 0x6EF8AA78),
        "require all eight group registers");

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
