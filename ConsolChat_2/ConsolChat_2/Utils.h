#pragma once
#include <string>
#include <functional>
#include <stdexcept>
#include <cctype>

inline std::size_t HashPassword(const std::string& password) {
    // Учебный хэш (НЕ крипто)
    return std::hash<std::string>{}(password);
}

inline bool IsBlank(const std::string& s) {
    for (unsigned char c : s) {
        if (!std::isspace(c)) return false;
    }
    return true;
}

inline void Require(bool cond, const std::string& msg) {
    if (!cond) throw std::runtime_error(msg);
}
