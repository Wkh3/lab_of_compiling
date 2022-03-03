#pragma once
#include <sstream>
#include <string>
#include <type_traits>

namespace lab{

template <typename T>
class TypeCast {
public:
    std::string operator()(const T &type) {
        return "";
    }
};


template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
class Token {
public:
    Token() = default;

    Token(T type, const std::string &v = "") : type_(type), value_(v) {}

    Token(const Token &rhs) : type_(rhs.type_), value_(rhs.value_) {}

    Token(Token &&rhs) noexcept : type_(rhs.type_), value_(std::move(rhs.value_)) {}

    Token& operator=(Token rhs) {
        rhs.swap(*this);
        return *this;
    }

    bool operator==(const Token &rhs) const {
        return type_ == rhs.type_ && value_ == rhs.value_;
    }

    bool operator!=(const Token &rhs) const {
        return !(*this == rhs);
    }

    void swap(Token &rhs) {
        std::swap(type_, rhs.type_);
        std::swap(value_, rhs.type_);
    }

    T getType() const {
        return type_;
    }

    void setType(T type) {
        type_ = type;
    }

    const std::string &getValue() const {
        return value_;
    }

    template <typename V>
    void setValue(V &&value) {
        value_ = std::forward<V>(value);
    }

    std::string toString() const {
        std::stringstream ss;
        ss << TypeCast<T>()(type_) << " : " << value_;
        return ss.str();
    }

protected:
    T type_;
    std::string value_;
};

}