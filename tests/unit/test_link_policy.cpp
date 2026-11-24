#include "pseries/link_policy.hpp"

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

pseries::PcieLinkInformation link(
    pseries::LinkGeneration current_generation,
    std::uint8_t current_width,
    pseries::LinkGeneration maximum_generation,
    std::uint8_t maximum_width,
    pseries::LinkTrainingState training = pseries::LinkTrainingState::stable) {
    return {
        current_generation,
        pseries::LinkWidth{current_width},
        maximum_generation,
        pseries::LinkWidth{maximum_width},
        training};
}

} // namespace

int main() {
    using pseries::LinkGeneration;

    const auto p104_gpu = link(LinkGeneration::gen2, 8, LinkGeneration::gen2, 16);
    const auto h61_upstream = link(LinkGeneration::gen2, 8, LinkGeneration::gen3, 8);
    const auto current = pseries::plan_link(p104_gpu, h61_upstream);
    expect(current.has_value(), "plan from stable P104/H61 link");
    if (current.has_value()) {
        expect(current.get().target_width.lanes == 8, "cap requested x16 to upstream x8");
        expect(current.get().target_generation == LinkGeneration::gen2, "cap speed to common Gen2");
        expect(!current.get().width_change_required, "do not widen an already-maximal x8 link");
        expect(!current.get().generation_change_required, "do not retune an already-Gen2 link");
    }

    const auto narrow_gpu = link(LinkGeneration::gen1, 4, LinkGeneration::gen2, 16);
    const auto narrow_upstream = link(LinkGeneration::gen1, 4, LinkGeneration::gen3, 8);
    const auto upgrade = pseries::plan_link(narrow_gpu, narrow_upstream);
    expect(upgrade.has_value(), "plan width and generation upgrades");
    if (upgrade.has_value()) {
        expect(upgrade.get().target_width.lanes == 8, "request maximum advertised x8");
        expect(upgrade.get().target_generation == LinkGeneration::gen2, "request common Gen2");
        expect(upgrade.get().width_change_required, "request width stage from x4");
        expect(upgrade.get().generation_change_required, "request speed stage from Gen1");
    }

    const auto x4_gpu = link(LinkGeneration::gen2, 4, LinkGeneration::gen2, 4);
    const auto x4_upstream = link(LinkGeneration::gen2, 4, LinkGeneration::gen3, 4);
    const auto x4_limit = pseries::plan_link(x4_gpu, x4_upstream);
    expect(
        x4_limit.has_value() && x4_limit.get().target_width.lanes == 4,
        "cap target to a narrower host path");

    const auto wider_gpu = link(LinkGeneration::gen2, 8, LinkGeneration::gen3, 16);
    const auto wider_upstream = link(LinkGeneration::gen2, 8, LinkGeneration::gen3, 16);
    const auto no_downgrade = pseries::plan_link(
        wider_gpu, wider_upstream, {4}, LinkGeneration::gen1);
    expect(
        no_downgrade.has_value() &&
            no_downgrade.get().target_width.lanes == 8 &&
            no_downgrade.get().target_generation == LinkGeneration::gen2 &&
            !no_downgrade.get().width_change_required &&
            !no_downgrade.get().generation_change_required,
        "never downgrade an already wider or faster link");

    expect(
        pseries::may_continue_generation_after_width_failure(
            narrow_gpu, narrow_upstream, LinkGeneration::gen2, true, true),
        "continue Gen2 at stable x4 after clean width failure");
    expect(
        !pseries::may_continue_generation_after_width_failure(
            narrow_gpu, narrow_upstream, LinkGeneration::gen2, false, true),
        "do not continue after incomplete transaction cleanup");
    expect(
        !pseries::may_continue_generation_after_width_failure(
            narrow_gpu, narrow_upstream, LinkGeneration::gen2, true, false),
        "do not continue when device is unhealthy");

    const auto unstable_upstream = link(
        LinkGeneration::gen1, 4, LinkGeneration::gen3, 8, pseries::LinkTrainingState::training);
    expect(
        !pseries::may_continue_generation_after_width_failure(
            narrow_gpu, unstable_upstream, LinkGeneration::gen2, true, true),
        "do not continue while either endpoint is training");
    expect(
        !pseries::plan_link(narrow_gpu, unstable_upstream).has_value(),
        "reject planning on unstable link");

    const auto incomplete = link(
        LinkGeneration::gen1, 4, LinkGeneration::gen2, 16);
    auto unknown_upstream = narrow_upstream;
    unknown_upstream.maximum_width.reset();
    expect(
        !pseries::plan_link(incomplete, unknown_upstream).has_value(),
        "reject incomplete endpoint capability data");

    const auto contradictory_upstream = link(
        LinkGeneration::gen3, 4, LinkGeneration::gen2, 8);
    expect(
        !pseries::plan_link(narrow_gpu, contradictory_upstream).has_value(),
        "reject current link speed above reported capability");

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
