#pragma once

#include <sstream>  // istringstream


namespace rtc::stream {
    inline auto get_unread(std::istringstream& iss) {
        return iss.eof() ? "" : iss.str().substr(static_cast<size_t>(iss.tellg()));
    }
}  // namespace rtc::stream
