#pragma once

#include "pseries/types.hpp"

#include <span>

namespace pseries {

[[nodiscard]] bool is_known_p_series_gpu(const HardwareIdentity& identity) noexcept;

[[nodiscard]] Result<HardwareIdentity> select_unique_p_series_gpu(
    std::span<const HardwareIdentity> devices);

} // namespace pseries
