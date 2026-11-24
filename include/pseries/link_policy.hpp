#pragma once

#include "pseries/types.hpp"

namespace pseries {

struct LinkPlan {
    LinkWidth target_width{};
    LinkGeneration target_generation{LinkGeneration::unknown};
    bool width_change_required{};
    bool generation_change_required{};
};

[[nodiscard]] Result<LinkPlan> plan_link(
    const PcieLinkInformation& gpu,
    const PcieLinkInformation& upstream,
    LinkWidth requested_width = {16},
    LinkGeneration requested_generation = LinkGeneration::gen2);

[[nodiscard]] bool may_continue_generation_after_width_failure(
    const PcieLinkInformation& gpu,
    const PcieLinkInformation& upstream,
    LinkGeneration requested_generation,
    bool transaction_cleanup_succeeded,
    bool device_healthy) noexcept;

} // namespace pseries
