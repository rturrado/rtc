#pragma once

#include <chrono>
#include <date/date.h>
#include <format>
#include <stdexcept>  // runtime_error
#include <string>


namespace rtc::chrono {
    struct invalid_date_error : public std::runtime_error {
        invalid_date_error(const date::year_month_day& ymd) : std::runtime_error{ std::format("{}", ymd) } {}
    };

    struct invalid_month_error : public std::runtime_error {
        invalid_month_error(const date::month& m) : std::runtime_error{ std::format("{}", m) } {}
    };
}  // namespace rtc::chrono
