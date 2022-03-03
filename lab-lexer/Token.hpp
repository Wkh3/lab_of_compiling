#pragma once
#include <type_traits>
#include <string>
template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>> 
class Token {

protected:
        T type_;
        std::string value_;
};
