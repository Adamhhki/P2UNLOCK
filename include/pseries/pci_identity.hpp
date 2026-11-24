#pragma once

#include "pseries/types.hpp"

#include <string_view>

namespace pseries {

[[nodiscard]] Result<HardwareIdentity> parse_pci_hardware_id(std::string_view text);

} // namespace pseries
