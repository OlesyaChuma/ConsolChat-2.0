#include "FileStorage.h"
#include <fstream>
#include <iomanip>   // quoted
#include <stdexcept>

std::string FileStorage::usersPath() const {
    return _dir + "/users.txt";
}

std::string FileStorage::messagesPath() const {
    return _dir + "/messages.txt";
}

void FileStorage::load(std::unordered_map<std::string, User>& users, std::vector<Message>& messages) {
    users.clear();
    messages.clear();

    // ---- users ----
    {
        std::ifstream in(usersPath());
        if (in) {
            std::string login, name;
            std::size_t passHash{};
            while (in >> std::quoted(login) >> passHash >> std::quoted(name)) {
                users.emplace(login, User(login, passHash, name));
            }
            if (!in.eof() && in.fail()) {
                throw std::runtime_error("Ошибка чтения users.txt (поврежден формат).");
            }
        }
    }

    // ---- messages ----
    {
        std::ifstream in(messagesPath());
        if (in) {
            std::string from, to, text;
            std::time_t ts{};
            while (in >> std::quoted(from) >> std::quoted(to) >> std::quoted(text) >> ts) {
                messages.emplace_back(from, to, text, ts);
            }
            if (!in.eof() && in.fail()) {
                throw std::runtime_error("Ошибка чтения messages.txt (поврежден формат).");
            }
        }
    }
}

void FileStorage::save(const std::unordered_map<std::string, User>& users, const std::vector<Message>& messages) {
    // ---- users ----
    {
        std::ofstream out(usersPath(), std::ios::trunc);
        if (!out) throw std::runtime_error("Не удалось открыть users.txt для записи.");

        for (const auto& [login, u] : users) {
            out << std::quoted(u.login()) << " " << u.passHash() << " " << std::quoted(u.name()) << "\n";
        }
    }

    // ---- messages ----
    {
        std::ofstream out(messagesPath(), std::ios::trunc);
        if (!out) throw std::runtime_error("Не удалось открыть messages.txt для записи.");

        for (const auto& m : messages) {
            out << std::quoted(m.from()) << " "
                << std::quoted(m.to()) << " "
                << std::quoted(m.text()) << " "
                << m.ts() << "\n";
        }
    }
}
