#include "rtc/typeinfo.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace rtc::typeinfo;


TEST(type_name, const_char) {
    const char c{};
    const int i{};
    const size_t st{};
    const long long ll{};
    const float f{};
    const double d{};
    const std::string arr[10]{};

#ifdef _MSC_VER
    EXPECT_EQ(type_name<decltype(c)>(), "const char");
    EXPECT_EQ(type_name<decltype(i)>(), "const int");
#ifdef _WIN64
    EXPECT_EQ(type_name<decltype(st)>(), "const unsigned __int64");
    EXPECT_EQ(type_name<decltype(ll)>(), "const __int64");
#endif
    EXPECT_EQ(type_name<decltype(f)>(), "const float");
    EXPECT_EQ(type_name<decltype(d)>(), "const double");

    EXPECT_EQ(type_name<decltype("")>(), "const char(&)[1]");
    EXPECT_EQ(type_name<decltype("hello")>(), "const char(&)[6]");

    EXPECT_EQ(type_name<decltype(arr)>(),
        "const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[10]");
#endif

#ifdef __GNUC__
    EXPECT_EQ(type_name<decltype(c)>(), "const char");
    EXPECT_EQ(type_name<decltype(i)>(), "const int");
#if __x86_64__
    EXPECT_EQ(type_name<decltype(st)>(), "const long unsigned int");
    EXPECT_EQ(type_name<decltype(ll)>(), "const long long int");
#endif
    EXPECT_EQ(type_name<decltype(f)>(), "const float");
    EXPECT_EQ(type_name<decltype(d)>(), "const double");

    EXPECT_EQ(type_name<decltype("")>(), "const char (&)[1]");
    EXPECT_EQ(type_name<decltype("hello")>(), "const char (&)[6]");

    EXPECT_EQ(type_name<decltype(arr)>(),
        "const std::__cxx11::basic_string<char> [10]");
#endif
}
