#pragma once

#include <chrono>
#include <format>
#include <stdexcept>  // runtime_error
#include <string>


namespace rtc::chrono {
    struct invalid_date_error : public std::runtime_error {
        invalid_date_error(const std::chrono::year_month_day& ymd) : std::runtime_error{ std::format("{}", ymd) } {}
    };
}  // namespace rtc::chrono
