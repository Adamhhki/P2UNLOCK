#include "pseries/link_policy.hpp"

#include <algorithm>

namespace pseries {

namespace {

bool is_valid_width(std::uint8_t lanes) noexcept {
    switch (lanes) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 12:
    case 16:
    case 32:
        return true;
    default:
        return false;
    }
}

bool is_valid_generation(LinkGeneration generation) noexcept {
    return generation >= LinkGeneration::gen1 && generation <= LinkGeneration::gen5;
}

Error make_error(ErrorCode code, const char* message) {
    return Error{code, message};
}

bool endpoints_are_stable_and_matching(
    const PcieLinkInformation& gpu,
    const PcieLinkInformation& upstream) noexcept {
    return gpu.training_state == LinkTrainingState::stable &&
        upstream.training_state == LinkTrainingState::stable &&
        is_valid_width(gpu.negotiated_width.lanes) &&
        gpu.negotiated_width.lanes == upstream.negotiated_width.lanes &&
        is_valid_generation(gpu.current_generation) &&
        gpu.current_generation == upstream.current_generation;
}

} // namespace

Result<LinkPlan> plan_link(
    const PcieLinkInformation& gpu,
    const PcieLinkInformation& upstream,
    LinkWidth requested_width,
    LinkGeneration requested_generation) {
    if (!is_valid_width(requested_width.lanes) || !is_valid_generation(requested_generation)) {
        return Result<LinkPlan>{{make_error(ErrorCode::invalid_argument, "Invalid requested PCIe target")}};
    }

    if (!gpu.maximum_width || !upstream.maximum_width ||
        !gpu.maximum_generation || !upstream.maximum_generation) {
        return Result<LinkPlan>{{make_error(ErrorCode::unsupported, "Endpoint link capabilities are incomplete")}};
    }

    if (!is_valid_width(gpu.maximum_width->lanes) ||
        !is_valid_width(upstream.maximum_width->lanes) ||
        !is_valid_generation(*gpu.maximum_generation) ||
        !is_valid_generation(*upstream.maximum_generation)) {
        return Result<LinkPlan>{{make_error(ErrorCode::unsupported, "Endpoint reported invalid link capabilities")}};
    }

    if (!endpoints_are_stable_and_matching(gpu, upstream)) {
        return Result<LinkPlan>{{make_error(
            ErrorCode::unsupported,
            "GPU and upstream links must be stable and matching before planning a change")}};
    }

    if (gpu.negotiated_width.lanes > gpu.maximum_width->lanes ||
        upstream.negotiated_width.lanes > upstream.maximum_width->lanes ||
        static_cast<std::uint8_t>(gpu.current_generation) >
            static_cast<std::uint8_t>(*gpu.maximum_generation) ||
        static_cast<std::uint8_t>(upstream.current_generation) >
            static_cast<std::uint8_t>(*upstream.maximum_generation)) {
        return Result<LinkPlan>{{make_error(ErrorCode::unsupported, "Negotiated link exceeds reported capability")}};
    }

    const auto advertised_width = std::min(gpu.maximum_width->lanes, upstream.maximum_width->lanes);
    const auto requested_ceiling = std::min(requested_width.lanes, advertised_width);
    const auto target_width = std::max(requested_ceiling, gpu.negotiated_width.lanes);

    const auto common_generation = std::min(
        static_cast<std::uint8_t>(*gpu.maximum_generation),
        static_cast<std::uint8_t>(*upstream.maximum_generation));
    const auto target_generation = std::max(
        std::min(static_cast<std::uint8_t>(requested_generation), common_generation),
        static_cast<std::uint8_t>(gpu.current_generation));

    const auto generation = static_cast<LinkGeneration>(target_generation);
    return Result<LinkPlan>{{LinkPlan{
        LinkWidth{target_width},
        generation,
        target_width > gpu.negotiated_width.lanes,
        target_generation > static_cast<std::uint8_t>(gpu.current_generation)}}};
}

bool may_continue_generation_after_width_failure(
    const PcieLinkInformation& gpu,
    const PcieLinkInformation& upstream,
    LinkGeneration requested_generation,
    bool transaction_cleanup_succeeded,
    bool device_healthy) noexcept {
    if (!transaction_cleanup_succeeded || !device_healthy ||
        !is_valid_generation(requested_generation) ||
        !endpoints_are_stable_and_matching(gpu, upstream) ||
        !gpu.maximum_generation || !upstream.maximum_generation ||
        !is_valid_generation(*gpu.maximum_generation) ||
        !is_valid_generation(*upstream.maximum_generation)) {
        return false;
    }

    const auto current = static_cast<std::uint8_t>(gpu.current_generation);
    const auto requested = static_cast<std::uint8_t>(requested_generation);
    return current < requested &&
        static_cast<std::uint8_t>(*gpu.maximum_generation) >= requested &&
        static_cast<std::uint8_t>(*upstream.maximum_generation) >= requested;
}

} // namespace pseries
