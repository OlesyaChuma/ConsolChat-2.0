#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "Utils.h"

inline std::string ReadLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    if (!std::cin) throw std::runtime_error("Input stream error.");
    return s;
}

inline std::string ReadNonEmptyLine(const std::string& prompt) {
    while (true) {
        std::string s = ReadLine(prompt);
        if (!s.empty() && !IsBlank(s)) return s;
        std::cout << "Пустая строка. Повторите ввод.\n";
    }
}

inline int ReadIntInRange(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        int x{};
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (x >= lo && x <= hi) return x;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Некорректный ввод. Введите число от " << lo << " до " << hi << ".\n";
    }
}
