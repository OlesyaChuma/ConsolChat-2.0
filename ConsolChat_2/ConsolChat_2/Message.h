#pragma once
#include <string>
#include <ctime>

class Message {
public:
    Message() = default;
    Message(std::string from, std::string to, std::string text, std::time_t ts)
        : _from(std::move(from)), _to(std::move(to)), _text(std::move(text)), _ts(ts) {
    }

    const std::string& from() const noexcept { return _from; }
    const std::string& to()   const noexcept { return _to; }
    const std::string& text() const noexcept { return _text; }
    std::time_t ts() const noexcept { return _ts; }

private:
    std::string _from;
    std::string _to;   // "all" => сообщение всем
    std::string _text;
    std::time_t _ts{};
};
