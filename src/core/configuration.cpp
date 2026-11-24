#include "pseries/configuration.hpp"

namespace pseries {

Result<ServiceConfiguration> validate_service_configuration(
    const ServiceConfiguration& configuration) noexcept {
    if (configuration.schema_version != 1u) {
        return Result<ServiceConfiguration>{{Error{
            ErrorCode::invalid_configuration,
            "Unsupported configuration schema version"}}};
    }
    if (configuration.hardware_modifications != HardwareModificationPolicy::disabled) {
        return Result<ServiceConfiguration>{{Error{
            ErrorCode::invalid_configuration,
            "No hardware modification policy is implemented"}}};
    }
    return Result<ServiceConfiguration>{{configuration}};
}

Result<ServiceConfiguration> parse_service_configuration(std::string_view text) noexcept {
    ServiceConfiguration result{};
    bool schema_seen = false;
    bool policy_seen = false;

    while (!text.empty()) {
        const std::size_t newline = text.find('\n');
        std::string_view line = text.substr(0, newline);
        if (newline == std::string_view::npos) {
            text = {};
        } else {
            text.remove_prefix(newline + 1);
        }

        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.remove_suffix(1);
        }
        if (line.empty() || line.front() == '#') {
            continue;
        }

        const std::size_t equals = line.find('=');
        if (equals == std::string_view::npos) {
            return Result<ServiceConfiguration>{{Error{
                ErrorCode::invalid_configuration, "Configuration line has no '='"}}};
        }
        const std::string_view key = line.substr(0, equals);
        const std::string_view value = line.substr(equals + 1);

        if (key == "schema_version") {
            schema_seen = true;
            if (value != "1") {
                return Result<ServiceConfiguration>{{Error{
                    ErrorCode::invalid_configuration, "Unsupported configuration schema"}}};
            }
            result.schema_version = 1;
        } else if (key == "hardware_modifications") {
            policy_seen = true;
            if (value != "disabled") {
                return Result<ServiceConfiguration>{{Error{
                    ErrorCode::invalid_configuration,
                    "Hardware modifications must remain disabled in this build"}}};
            }
        } else {
            return Result<ServiceConfiguration>{{Error{
                ErrorCode::invalid_configuration, "Unknown configuration key"}}};
        }
    }

    if (!schema_seen || !policy_seen) {
        return Result<ServiceConfiguration>{{Error{
            ErrorCode::invalid_configuration,
            "Required configuration values are missing"}}};
    }
    return validate_service_configuration(result);
}

} // namespace pseries
