#include "pseries/logging.hpp"

#include <cstdlib>
#include <iostream>

int main() {
    const auto text = pseries::format_log_record(
        {"INFO", "service", "startup initialized"},
        std::chrono::system_clock::from_time_t(0));
    if (text.find("level=INFO") == std::string::npos ||
        text.find("component=service") == std::string::npos ||
        text.find("startup initialized") == std::string::npos) {
        std::cerr << "FAILED: structured log format\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
