#pragma once
#include <string>
#include <variant>
#include <vector>
#include <iostream>
#include <type_traits>
#include <cstdint>

namespace x
{

using var = std::variant<bool, char, int64_t, uint64_t, double, std::string>;

template<typename T>
constexpr var make_var(T&& value)
{
    using type = std::decay_t<T>;
    if constexpr(std::is_same_v<type, bool>){
        return var(bool(value));
    }else if constexpr(std::is_same_v<type, char>){
        return var(char(value));
    }else if constexpr(std::is_integral_v<type>){
        if constexpr(std::is_signed_v<type>){
            return var(static_cast<int64_t>(value));
        }else{
            return var(static_cast<uint64_t>(value));
        }
    }else if constexpr(std::is_floating_point_v<type>){
        return var(static_cast<double>(value));
    }else if constexpr(std::is_convertible_v<type, std::string>){
        return var(std::string(std::forward<T>(value)));
    }else{
        static_assert(sizeof(T) == 0, "unsupported type");
    }
}

std::string FormatDetail(std::string& fmt, const std::vector<var>& vargs);

/**
 * @brief 格式化字符串
 */
template <typename... Args>
std::string Format(const std::string &fmt, Args...args)
{
    std::vector<var> vargs = {make_var(args)...};
    std::string str = fmt;
    return FormatDetail(str, vargs);
}

}