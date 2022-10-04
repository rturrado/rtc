#pragma once

#include <algorithm>  // binary_search, count_if, sort
#include <charconv>  // from_chars
#include <cctype>  // isdigit
#if defined _WIN32
#include <conio.h>  // _getch
#endif
#include <cstdlib>  // system
#include <fmt/ranges.h>
#include <fmt/ostream.h>
#include <ios>  // dec, streamsize
#include <iostream>  // cin, cout
#include <istream>
#include <limits>  // numeric_limits
#include <ostream>
#include <sstream>  // istringstream
#include <stdexcept>  // invalid_argument, out_of_range
#include <string>  // getline, stol
#include <system_error>  // errc
#include <vector>


namespace rtc::console {
    // Check if input stream is clear
    inline bool is_istream_clear(const std::istream& is) {
        return (is.rdbuf()->in_avail() == 0);
    }


    // Clear input stream
    inline void clear_istream(std::istream& is) {
        is.clear();
        if (std::streamsize n = is.rdbuf()->in_avail()) {  // ignores whatever there may be within is
            is.ignore(n);
        }
    }


    // Read a char from a possible list of options
    inline char read_char(
        std::istream& is,
        std::ostream& os,
        const std::string& message,
        std::vector<char> options) {

        if (options.empty()) {
            return '\0';
        }

        std::sort(std::begin(options), std::end(options));

        for (;;) {
            fmt::print(os, "{}", message);
            std::string s{};
            std::getline(is, s);
            if (s.size() == 1 and std::binary_search(std::cbegin(options), std::cend(options), s[0])) {
                fmt::print(os, "\tOK\n");
                return s[0];
            }
            fmt::print(os, "\tError: invalid input\n");
        }
    }

    inline char read_char(const std::string& message, std::vector<char> options) {
        return read_char(std::cin, std::cout, message, std::move(options));
    }


    // Read a positive number in the range [lower_limit, upper_limit)
    // or [lower_limit, INT_MAX) in case upper_limit is not specified
    inline int read_positive_number(
        std::istream& is,
        std::ostream& os,
        const std::string& message,
        int lower_limit,
        int upper_limit = (std::numeric_limits<int>::max)()) {

        for (;;) {
            fmt::print(os, "{}", message);

            std::string n_str{};
            std::getline(is, n_str);

            int n{ 0 };
            auto [ptr, ec] { std::from_chars(n_str.data(), n_str.data() + n_str.size(), n) };
            if (ec != std::errc{}) {
                fmt::print(os, "\tError: invalid input\n");
            } else {
                if (ptr != n_str.data() + n_str.size()) {
                    fmt::print(os, "\tError: invalid input\n");
                } else if (n < 0 or n < lower_limit or n >= upper_limit) {
                    fmt::print(os, "\tError: number not within the limits\n");
                } else {
                    fmt::print(os, "\tOK\n");
                    return n;
                }
            }
        }
    }

    inline int read_positive_number(
        const std::string& message,
        int lower_limit,
        int upper_limit = (std::numeric_limits<int>::max)()) {

        return read_positive_number(std::cin, std::cout, message, lower_limit, upper_limit);
    }


    // Read a list of positive numbers in the range [lower_limit, upper_limit)
    // or [lower_limit, INT_MAX) in case upper_limit is not specified
    // minimum_list_size is the minimum number of the elements to read for the list
    // The list is expected to end with the string 'quit'
    inline std::vector<int> read_list_of_positive_numbers(
        std::istream& is,
        std::ostream& os,
        const std::string& message,
        size_t minimum_list_size,
        int lower_limit,
        int upper_limit = (std::numeric_limits<int>::max)()) {

        if (minimum_list_size == 0) {
            return std::vector<int>{};
        }
        for (;;) {
            fmt::print(os, "{}", message);

            std::vector<int> v{};
            bool quit_read{ false };
            bool valid_input{ true };

            while ((not quit_read) and valid_input) {
                std::string line{};
                std::getline(is, line);  // read line

                std::istringstream iss{ line };
                for (std::string s{}; (not quit_read) and valid_input and iss >> s;) {  // line can contain several tokens
                    if (s == "quit") {
                        if (not is_istream_clear(iss)) {
                            fmt::print(os, "\tError: invalid input\n");
                            valid_input = false;
                        } else {
                            quit_read = true;
                        }
                    } else {
                        int i{ 0 };
                        auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), i);
                        if (ec == std::errc{}) {
                            if (ptr != s.data() + s.size()) {
                                fmt::print(os, "\tError: invalid input\n");
                                valid_input = false;
                            } else if (i < 0 || i < lower_limit || i >= upper_limit) {
                                fmt::print(os, "\tError: number {} not within the limits\n", i);
                                valid_input = false;
                            } else {
                                v.push_back(i);
                            }
                        } else {
                            fmt::print(os, "\tError: invalid input\n");
                            valid_input = false;
                        }
                    }
                }
            }

            if (quit_read and valid_input and v.size() >= minimum_list_size) {
                fmt::print(os, "\tOK\n");
                return v;
            }
        }
    }


    inline std::vector<int> read_list_of_positive_numbers(
        const std::string& message,
        size_t minimum_list_size,
        int lower_limit,
        int upper_limit = (std::numeric_limits<int>::max)()) {

        return read_list_of_positive_numbers(std::cin, std::cout, message, minimum_list_size, lower_limit, upper_limit);
    }


    // Read an n-digit string
    inline std::string read_n_digit_string(size_t n) {
        std::string ret{};

        bool valid_input{ false };
        while (!valid_input) {
            std::cout << "Please enter a " << n << " digit string: ";
            std::cin >> ret;
            if (ret.size() != n ||
                std::count_if(ret.begin(), ret.end(), [](auto& n) { return std::isdigit(n) != 0; }) != 10) {

                std::cout << "\tError: invalid input\n";
            } else {
                valid_input = true;
            }
            if (!valid_input) {
                clear_istream(std::cin);
            }
        }

        return ret;
    }


    inline void clear_screen() {
#if defined _WIN32
        ([[maybe_unused]] int i{ std::system("cls") };
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        [[maybe_unused]] int i{ std::system("clear") };
#elif defined (__APPLE__)
        [[maybe_unused]] int i{ std::system("clear") };
#endif
    }


    inline void wait_for_key_pressed() {
#if defined _WIN32
        [[maybe_unused]] int i{ _getch() };
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        [[maybe_unused]] int i{ std::system("read") };
#elif defined (__APPLE__)
        ([[maybe_unused]] int i{ std::system("read") };
#endif
    }
}  // namespace rtc::console
