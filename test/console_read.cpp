#include "rtc/console_read.h"

#include <fmt/core.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <istream>
#include <ostream>

using namespace rtc::console;


TEST(read_positive_number, invalid_input) {
    std::istringstream iss{ "abc\n1\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 1);
}

TEST(read_positive_number, number_with_the_limits_followed_by_invalid_input) {
    std::istringstream iss{ "1 abc\n2\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 2);
}

TEST(read_positive_number, number_not_within_the_limits) {
    std::istringstream iss{ "123\n4\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: number not within the limits"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 4);
}

TEST(read_positive_number, negative_number) {
    std::istringstream iss{ "-1\n2\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: number not within the limits"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 2);
}

TEST(read_positive_number, floating_number) {
    std::istringstream iss{ "1.2\n3\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 3);
}

TEST(read_positive_number, lower_limit) {
    std::istringstream iss{ "0\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 0);
}

TEST(read_positive_number, number_within_the_limits) {
    std::istringstream iss{ "1\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 1);
}

TEST(read_positive_number, upper_limit) {
    std::istringstream iss{ "10\n0\n" };
    std::ostringstream oss{};
    int lower_limit{ 0 };
    int upper_limit{ 10 };
    auto message{ fmt::format("Please enter a positive number between {} and {}: ", lower_limit, upper_limit) };
    auto ret{ read_positive_number(iss, oss, message, lower_limit, upper_limit) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: number not within the limits"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 0);
}
