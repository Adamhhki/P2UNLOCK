#pragma once

#include "pseries/types.hpp"

#include <cstdint>
#include <string_view>

namespace pseries {

enum class HardwareModificationPolicy : std::uint8_t {
    disabled,
};

struct ServiceConfiguration {
    std::uint32_t schema_version{1};
    HardwareModificationPolicy hardware_modifications{HardwareModificationPolicy::disabled};
};

Result<ServiceConfiguration> validate_service_configuration(
    const ServiceConfiguration& configuration) noexcept;

Result<ServiceConfiguration> parse_service_configuration(std::string_view text) noexcept;

} // namespace pseries
