#pragma once
#include <unordered_map>
#include <vector>
#include <optional>
#include <string>
#include "User.h"
#include "Message.h"
#include "FileStorage.h"

class Chat {
public:
    explicit Chat(FileStorage storage);

    // persistence
    void load();
    void save();

    // auth
    void registerUser(const std::string& login, const std::string& password, const std::string& name);
    void loginUser(const std::string& login, const std::string& password);
    void logout();

    bool isLoggedIn() const noexcept { return _current.has_value(); }
    const std::string& currentLogin() const;

    // messaging
    void sendToUser(const std::string& toLogin, const std::string& text);
    void sendToAll(const std::string& text);
    void printInboxForCurrent() const;

    // helpers
    bool userExists(const std::string& login) const;

private:
    std::unordered_map<std::string, User> _users;
    std::vector<Message> _messages;
    std::optional<std::string> _current; // login
    FileStorage _storage;

    static std::string FormatTime(std::time_t t);
};
