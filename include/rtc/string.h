#pragma once

#include <algorithm>  // transform
#include <cctype>  // tolower
#include <string>


namespace rtc::string {
    inline std::string to_lowercase(std::string str) {
        std::ranges::transform(str, std::begin(str), [](unsigned char c) { return std::tolower(c); });
        return str;
    }

    inline auto trim_right(const std::string& str) {
        return str.substr(0, str.find_last_not_of(' ') + 1);
    }
}  // namespace rtc::string
