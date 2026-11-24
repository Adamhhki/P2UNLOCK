#include "pseries/logging.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace pseries {

std::string format_log_record(
    LogRecord record,
    std::chrono::system_clock::time_point now) {
    const auto time = std::chrono::system_clock::to_time_t(now);
    std::tm utc{};
#if defined(_WIN32)
    gmtime_s(&utc, &time);
#else
    gmtime_r(&time, &utc);
#endif
    std::ostringstream output;
    output << std::put_time(&utc, "%Y-%m-%dT%H:%M:%SZ")
           << " level=" << record.level
           << " component=" << record.component
           << " message=\"" << record.message << "\"";
    return output.str();
}

} // namespace pseries
