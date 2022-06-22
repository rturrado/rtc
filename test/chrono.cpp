#include "rtc/chrono.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <string>

using namespace rtc::chrono;
using namespace std::chrono_literals;


TEST(invalid_date_error, constructor) {
    EXPECT_THAT(
        std::string{ invalid_date_error{ 2022y / 20 / 50 }.what() },
        ::testing::ContainsRegex("2022.20.50 is not a valid date")
    );
}
