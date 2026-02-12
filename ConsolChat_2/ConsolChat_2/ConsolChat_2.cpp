// ConsolChat_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Chat.h"
#include "Input.h"
#include <Windows.h>

static void PrintMainMenu(bool loggedIn, const std::string& who) {
    std::cout << "\n===== ConsoleChat =====\n";
    if (loggedIn) std::cout << "Вы вошли как: " << who << "\n";
    std::cout
        << "1) Регистрация\n"
        << "2) Вход\n"
        << "3) Отправить личное сообщение\n"
        << "4) Отправить сообщение всем\n"
        << "5) Показать мои сообщения\n"
        << "6) Выход из аккаунта\n"
        << "7) Сохранить\n"
        << "0) Выход из программы\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    try {
        Chat chat(FileStorage(".")); // файлы рядом с exe
        try {
            chat.load();
            std::cout << "Данные загружены.\n";
        }
        catch (const std::exception& e) {
            std::cout << "Предупреждение: не удалось загрузить данные: " << e.what() << "\n";
        }

        while (true) {
            PrintMainMenu(chat.isLoggedIn(), chat.isLoggedIn() ? chat.currentLogin() : std::string("-"));
            int cmd = ReadIntInRange("Выберите пункт: ", 0, 7);

            try {
                if (cmd == 0) {
                    // Автосохранение при выходе
                    chat.save();
                    std::cout << "Сохранено. До свидания!\n";
                    break;
                }
                else if (cmd == 1) {
                    std::string login = ReadNonEmptyLine("Логин: ");
                    std::string pass = ReadNonEmptyLine("Пароль: ");
                    std::string name = ReadNonEmptyLine("Имя: ");
                    chat.registerUser(login, pass, name);
                    std::cout << "Регистрация успешна.\n";
                }
                else if (cmd == 2) {
                    std::string login = ReadNonEmptyLine("Логин: ");
                    std::string pass = ReadNonEmptyLine("Пароль: ");
                    chat.loginUser(login, pass);
                    std::cout << "Вход выполнен.\n";
                }
                else if (cmd == 3) {
                    std::string to = ReadNonEmptyLine("Кому (логин): ");
                    std::string text = ReadNonEmptyLine("Текст: ");
                    chat.sendToUser(to, text);
                    std::cout << "Сообщение отправлено.\n";
                }
                else if (cmd == 4) {
                    std::string text = ReadNonEmptyLine("Текст: ");
                    chat.sendToAll(text);
                    std::cout << "Сообщение всем отправлено.\n";
                }
                else if (cmd == 5) {
                    chat.printInboxForCurrent();
                }
                else if (cmd == 6) {
                    chat.logout();
                    std::cout << "Вы вышли из аккаунта.\n";
                }
                else if (cmd == 7) {
                    chat.save();
                    std::cout << "Сохранено.\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "Критическая ошибка: " << e.what() << "\n";
        return 1;
    }
}
