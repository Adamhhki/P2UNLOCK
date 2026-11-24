#pragma once

#include <chrono>
#include <string>
#include <string_view>

namespace pseries {

struct LogRecord {
    std::string level;
    std::string component;
    std::string message;
};

[[nodiscard]] std::string format_log_record(
    LogRecord record,
    std::chrono::system_clock::time_point now);

} // namespace pseries
