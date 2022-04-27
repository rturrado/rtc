#pragma once

#include <algorithm>  // for_each, sort
#include <concepts>
#include <iomanip>  // setfill, setw
#include <ios>  // dec, hex
#include <ostream>
#include <utility>  // pair


namespace rtc::print {
    template <typename T>
    concept printable = requires (std::ostream& os, const T& t) {
        os << t;
    };

    template <typename C>
    concept implements_operator_extraction = requires (std::ostream& os, const C& c) {
        os << c;
    };

    // Print container
    template <typename C>
        requires (!std::same_as<typename C::value_type, uint8_t>)
        && (!std::same_as<typename C::value_type, char>)
        && (!std::is_convertible_v<typename C::value_type, std::string_view>)
        && (!implements_operator_extraction<C>)
        && printable<typename C::value_type>
    std::ostream& operator<<(std::ostream& os, const C& c) {
        os << "{";
        std::for_each(cbegin(c), cend(c), [first = true, &os](const auto& n) mutable {
            os << (first ? " " : ", ") << n;
            first = false;
        });
        os << " }";
        return os;
    };

    // Print container of uint8_t
    template <typename C>
        requires std::same_as<typename C::value_type, uint8_t> && (!implements_operator_extraction<C>)
    std::ostream& operator<<(std::ostream& os, const C& c) {
        os << "{";
        std::for_each(cbegin(c), cend(c), [first = true, &os](const auto& n) mutable {
            os << (first ? " " : ", ") << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(n) << std::dec;
            first = false;
        });
        os << " }";
        return os;
    };

    // Print container of chars
    template <typename C>
        requires std::same_as<typename C::value_type, char> && (!implements_operator_extraction<C>)
    std::ostream& operator<<(std::ostream& os, const C& c) {
        os << "{";
        std::for_each(cbegin(c), cend(c), [first = true, &os](const auto& n) mutable {
            os << (first ? " " : ", ") << "'" << n << "'";
            first = false;
        });
        os << " }";
        return os;
    };

    // Print container of strings
    template <typename C>
        requires std::is_convertible_v<typename C::value_type, std::string_view> && (!implements_operator_extraction<C>)
    std::ostream& operator<<(std::ostream& os, const C& c) {
        os << "{";
        std::for_each(cbegin(c), cend(c), [first = true, &os](const auto& n) mutable {
            os << (first ? " " : ", ") << "\"" << n << "\"";
            first = false;
        });
        os << " }";
        return os;
    };


    // Print pair
    template<typename T, typename U = T>
    std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
        return os << "[" << p.first << ", " << p.second << "]";
    }
}  // namespace rtc::print
