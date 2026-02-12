#include "Chat.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

Chat::Chat(FileStorage storage)
    : _storage(std::move(storage)) {
}

void Chat::load() {
    _storage.load(_users, _messages);
}

void Chat::save() {
    _storage.save(_users, _messages);
}

void Chat::registerUser(const std::string& login, const std::string& password, const std::string& name) {
    Require(!login.empty() && !IsBlank(login), "Логин не может быть пустым.");
    Require(!password.empty() && !IsBlank(password), "Пароль не может быть пустым.");
    Require(!name.empty() && !IsBlank(name), "Имя не может быть пустым.");
    Require(_users.find(login) == _users.end(), "Пользователь с таким логином уже существует.");

    _users.emplace(login, User(login, HashPassword(password), name));
}

void Chat::loginUser(const std::string& login, const std::string& password) {
    auto it = _users.find(login);
    Require(it != _users.end(), "Пользователь не найден.");
    Require(it->second.passHash() == HashPassword(password), "Неверный пароль.");
    _current = login;
}

void Chat::logout() {
    _current.reset();
}

const std::string& Chat::currentLogin() const {
    if (!_current) throw std::runtime_error("Нет авторизованного пользователя.");
    return *_current;
}

bool Chat::userExists(const std::string& login) const {
    return _users.find(login) != _users.end();
}

void Chat::sendToUser(const std::string& toLogin, const std::string& text) {
    Require(isLoggedIn(), "Сначала выполните вход.");
    Require(userExists(toLogin), "Получатель не найден.");
    Require(!text.empty() && !IsBlank(text), "Текст сообщения пуст.");

    _messages.emplace_back(currentLogin(), toLogin, text, std::time(nullptr));
}

void Chat::sendToAll(const std::string& text) {
    Require(isLoggedIn(), "Сначала выполните вход.");
    Require(!text.empty() && !IsBlank(text), "Текст сообщения пуст.");

    _messages.emplace_back(currentLogin(), "all", text, std::time(nullptr));
}

std::string Chat::FormatTime(std::time_t t) {
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    tm = *std::localtime(&t);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Chat::printInboxForCurrent() const {
    Require(isLoggedIn(), "Сначала выполните вход.");

    const std::string me = *_current;

    std::cout << "\n=== Сообщения для " << me << " ===\n";
    bool any = false;

    for (const auto& m : _messages) {
        const bool visible =
            (m.to() == "all") ||
            (m.to() == me) ||
            (m.from() == me); // показываем и отправленные

        if (visible) {
            any = true;
            std::cout << "[" << FormatTime(m.ts()) << "] "
                << m.from() << " -> " << m.to()
                << " : " << m.text() << "\n";
        }
    }

    if (!any) std::cout << "(пока нет сообщений)\n";
    std::cout << "=========================\n\n";
}
