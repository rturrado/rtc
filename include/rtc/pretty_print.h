#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <ostream>
#include <range/v3/view/repeat_n.hpp>
#include <string>


namespace rtc::pretty_print {
    const auto default_indentation_value{ "    " };

    struct indentation {
        size_t level{};
        std::string value{ default_indentation_value };
    };

    inline indentation operator+(const indentation& i, size_t increase) {
        return indentation{ i.level + increase, i.value };
    }
    inline indentation operator+(size_t increase, const indentation& i) {
        return i + increase;
    }
}  // namespace rtc::pretty_print


template<>
struct fmt::formatter<rtc::pretty_print::indentation> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const rtc::pretty_print::indentation& i, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", fmt::join(ranges::views::repeat_n(i.value, i.level), ""));
    }
};

inline std::ostream& operator<<(std::ostream& os, const rtc::pretty_print::indentation& i) {
    fmt::print(os, "{}", i);
    return os;
}
