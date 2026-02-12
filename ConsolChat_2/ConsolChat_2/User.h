#pragma once
#include <string>

class User {
public:
    User() = default;
    User(std::string login, std::size_t passHash, std::string name)
        : _login(std::move(login)), _passHash(passHash), _name(std::move(name)) {
    }

    const std::string& login() const noexcept { return _login; }
    const std::string& name()  const noexcept { return _name; }
    std::size_t passHash() const noexcept { return _passHash; }

private:
    std::string _login;
    std::size_t _passHash{};
    std::string _name;
};
