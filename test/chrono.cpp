#include "rtc/chrono.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <string>

namespace ch = std::chrono;
using namespace rtc::chrono;
using namespace std::chrono_literals;


TEST(invalid_date_error, constructor) {
    EXPECT_THAT(
        std::string{ invalid_date_error{ 2022y / 20 / 50 }.what() },
        ::testing::ContainsRegex("2022.20.50 is not a valid date")
    );
}

TEST(invalid_month_error, constructor) {
    EXPECT_THAT(
        std::string{ invalid_month_error{ ch::month{ 20 } }.what() },
        ::testing::HasSubstr("20 is not a valid month")
    );
}
