#include "rtc/typeinfo.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

using namespace rtc::typeinfo;


TEST(type_name, const_char) {
#ifdef _MSC_VER
    const char c{}; EXPECT_EQ(type_name<decltype(c)>(), "const char");
    const int i{}; EXPECT_EQ(type_name<decltype(i)>(), "const int");
#ifdef _WIN64
    const size_t st{}; EXPECT_EQ(type_name<decltype(st)>(), "const unsigned __int64");
    const long long ll{}; EXPECT_EQ(type_name<decltype(ll)>(), "const __int64");
#endif
    const float f{}; EXPECT_EQ(type_name<decltype(f)>(), "const float");
    const double d{}; EXPECT_EQ(type_name<decltype(d)>(), "const double");

    EXPECT_EQ(type_name<decltype("")>(), "const char(&)[1]");
    EXPECT_EQ(type_name<decltype("hello")>(), "const char(&)[6]");

    const std::string arr[10]{}; EXPECT_EQ(type_name<decltype(arr)>(),
        "const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[10]");
#endif
}
