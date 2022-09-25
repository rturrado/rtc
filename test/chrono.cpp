#include "rtc/chrono.h"

#include "date/date.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>

using namespace rtc::chrono;
using namespace date::literals;


TEST(invalid_date_error, constructor) {
    EXPECT_THAT(
        std::string{ invalid_date_error{ 2022_y / 20 / 50 }.what() },
        ::testing::ContainsRegex("2022.20.50 is not a valid date")
    );
}

TEST(invalid_month_error, constructor) {
    EXPECT_THAT(
        std::string{ invalid_month_error{ date::month{ 20 } }.what() },
        ::testing::HasSubstr("20 is not a valid month")
    );
}
