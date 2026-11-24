#include "pseries/types.hpp"

#include <charconv>
#include <system_error>

namespace pseries {

namespace {

bool parse_hex(std::string_view text, auto& output) {
    const char* begin = text.data();
    const char* end = text.data() + text.size();
    const auto parsed = std::from_chars(begin, end, output, 16);
    return parsed.ec == std::errc{} && parsed.ptr == end;
}

} // namespace

bool PciBdf::is_valid() const noexcept {
    return device <= 0x1fu && function <= 0x07u;
}

Result<PciBdf> parse_pci_bdf(std::string_view text) {
    if (text.size() != 12u) {
        return Result<PciBdf>{{Error{ErrorCode::invalid_argument, "Expected BDF format DDDD:BB:DD.F"}}};
    }
    if (text[4] != ':' || text[7] != ':' || text[10] != '.') {
        return Result<PciBdf>{{Error{ErrorCode::invalid_argument, "Invalid BDF separators"}}};
    }

    PciBdf bdf{};
    std::uint16_t domain{};
    std::uint16_t bus{};
    std::uint16_t device{};
    std::uint16_t function{};

    if (!parse_hex(text.substr(0, 4), domain) ||
        !parse_hex(text.substr(5, 2), bus) ||
        !parse_hex(text.substr(8, 2), device) ||
        !parse_hex(text.substr(11, 1), function)) {
        return Result<PciBdf>{{Error{ErrorCode::invalid_argument, "BDF contains non-hexadecimal data"}}};
    }

    bdf.domain = domain;
    bdf.bus = static_cast<std::uint8_t>(bus);
    bdf.device = static_cast<std::uint8_t>(device);
    bdf.function = static_cast<std::uint8_t>(function);

    if (!bdf.is_valid()) {
        return Result<PciBdf>{{Error{ErrorCode::invalid_argument, "BDF is outside PCI limits"}}};
    }

    return Result<PciBdf>{{bdf}};
}

} // namespace pseries
