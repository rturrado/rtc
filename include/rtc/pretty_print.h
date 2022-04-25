#pragma once

#include <algorithm>  // fill_n
#include <iterator>  // ostream_iterator
#include <ostream>
#include <string>


namespace rtc::pretty_print {
    struct indentation {
        size_t level{};
        std::string value{ "    " };
    };

    inline std::ostream& operator<<(std::ostream& os, const indentation& i) {
        std::fill_n(std::ostream_iterator<std::string>(os), i.level, i.value);
        return os;
    }

    inline indentation operator+(const indentation& i, size_t increase) {
        return indentation{ i.level + increase, i.value };
    }
    inline indentation operator+(size_t increase, const indentation& i) {
        return i + increase;
    }
}  // namespace rtc::pretty_print
