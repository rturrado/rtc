#include "rtc/pretty_print.h"

#include "fmt/format.h"
#include "fmt/ostream.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream

using namespace rtc::pretty_print;


TEST(operator_extraction, default_indentation) {
    std::ostringstream oss{};
    oss << indentation{} << 25 << "\n";
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("{}{}{}", "", 25, "\n")));
}
TEST(operator_extraction, custom_indentation) {
    std::ostringstream oss{};
    oss << indentation{1, "***"} << 25 << "\n";
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("{}{}{}", "***", 25, "\n")));
}

TEST(fmt_print, default_indentation) {
    std::ostringstream oss{};
    fmt::print(oss, "{}{}{}", indentation{}, 25, "\n");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("{}{}{}", "", 25, "\n")));
}
TEST(fmt_print, custom_indentation) {
    std::ostringstream oss{};
    fmt::print(oss, "{}{}{}", indentation{1, "***"}, 25, "\n");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("{}{}{}", "***", 25, "\n")));
}

TEST(indentation_plus_increase, n_1) {
    std::ostringstream oss{};
    fmt::print(oss, "{}{}{}", indentation{} + 1, 25, "\n");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("{}{}{}", default_indentation_value, 25, "\n")));
}
TEST(increase_plus_indentation, n_1) {
    std::ostringstream oss{};
    fmt::print(oss, "{}{}{}", 1 + indentation{}, 25, "\n");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("{}{}{}", default_indentation_value, 25, "\n")));
}
