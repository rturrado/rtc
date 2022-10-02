#pragma once

#include <date/date.h>
#include <fmt/format.h>
#include <stdexcept>  // runtime_error
#include <string>


namespace rtc::chrono {
    struct invalid_date_error : public std::runtime_error {
        explicit invalid_date_error(const date::year_month_day& ymd) : std::runtime_error{ "" } {
            message_ = fmt::format(
                "{:04}-{:02}-{:02} is not a valid date",
                int(ymd.year()), unsigned(ymd.month()), unsigned(ymd.day())
            );
        }
        [[nodiscard]] const char* what() const noexcept override { return message_.c_str(); }
    private:
        std::string message_{};
    };

    struct invalid_month_error : public std::runtime_error {
        explicit invalid_month_error(const date::month& m)
            : std::runtime_error{ fmt::format("{} is not a valid month", unsigned(m)) }
        {}
    };
}  // namespace rtc::chrono
