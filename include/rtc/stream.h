#ifndef RTC_STREAM_H
#define RTC_STREAM_H

#include <sstream>  // istringstream


namespace rtc::stream
{
    inline auto get_unread(std::istringstream& iss)
    {
        return iss.eof() ? "" : iss.str().substr(iss.tellg());
    }

}  // namespace rtc::stream


#endif  // RTC_STREAM_H
