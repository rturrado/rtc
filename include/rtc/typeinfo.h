#pragma once

#include <string_view>


namespace rtc::typeinfo {
    template <typename T>
    constexpr auto type_name() {
        std::string_view name{};
        std::string_view prefix{};
        std::string_view suffix{};
#ifdef __clang__
        name = __PRETTY_FUNCTION__;
        prefix = "auto rtc::typeinfo::type_name() [T = ";
        suffix = "]";
#elif defined(__GNUC__)
        name = __PRETTY_FUNCTION__;
        prefix = "constexpr auto rtc::typeinfo::type_name() [with T = ";
        suffix = "]";
#elif defined(_MSC_VER)
        name = __FUNCSIG__;
        prefix = "auto __cdecl rtc::typeinfo::type_name<";
        suffix = ">(void)";
#endif
        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());
        return name;
    }
}  // namespace rtc::typeinfo
