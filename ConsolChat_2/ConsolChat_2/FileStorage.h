#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "User.h"
#include "Message.h"

class FileStorage {
public:
    explicit FileStorage(std::string dir = ".")
        : _dir(std::move(dir)) {
    }

    void load(std::unordered_map<std::string, User>& users, std::vector<Message>& messages);
    void save(const std::unordered_map<std::string, User>& users, const std::vector<Message>& messages);

private:
    std::string usersPath() const;
    std::string messagesPath() const;

    std::string _dir;
};
