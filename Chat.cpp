#include "Chat.h"
#include <iostream>

using namespace std;

shared_ptr<User> Chat::findUserByLogin(const string& login) {
    for (auto& user : users) {
        if (user->getLogin() == login)
            return user;
    }
    return nullptr;
}

void Chat::registerUser() {
    cout << "Регистрация нового пользователя" << endl ;
    string login, password, name;

    cout << "Введите логин: " << endl;
    cin >> login;

    if (findUserByLogin(login)) {
        cout << "Такой логин уже существует " << endl;
        return;
    }

    cout << "Введите пароль: ";
    cin >> password;
    cout << "Введите имя: ";
    cin.ignore();
    getline(cin, name);

    users.push_back(make_shared<User>(login, password, name));
    cout << "Пользователь успешно зарегистрирован" << endl;
}

void Chat::login() {
    cout << "Вход в систему" << endl;
    string login, password;
    cout << "Логин: ";
    cin >> login;
    cout << "Пароль: ";
    cin >> password;

    auto user = findUserByLogin(login);
    if (user && user->getPassword() == password) {
        loggedInUser = user;
        cout << "Добро пожаловать, " << user->getName() << " " << endl;
    }
    else {
        cout << "Неверный логин или пароль" << endl;
    }
}

void Chat::logout() {
    if (loggedInUser) {
        cout << "Пользователь " << loggedInUser->getName() << " вышел из системы" << endl;
        loggedInUser.reset();
    }
    else {
        cout << "Вы не вошли в систему" << endl;
    }
}

void Chat::sendMessage() {
    if (!loggedInUser) {
        cout << "Сначала войдите в систему" << endl;
        return;
    }

    cout << "Введите логин получателя (или 'all' для сообщения всем):" << endl;
    string to;
    cin >> to;

    cout << "Введите сообщение: " << endl;
    cin.ignore();
    string text;
    getline(cin, text);

    if (to == "all") {
        int sentCount = 0;
        for (auto& user : users) {
            if (user->getLogin() != loggedInUser->getLogin()) {
                user->addMessage("[Общий чат] " + loggedInUser->getName() + ": " + text);
                sentCount++;
            }
        }
        cout << "Сообщение отправлено " << sentCount << " пользователям" << endl;
    }
    else {
        auto user = findUserByLogin(to);
        if (user) {
            user->addMessage("[Личное] " + loggedInUser->getName() + ": " + text);
            cout << "Сообщение отправлено пользователю " << user->getName() << "." << endl;
        }
        else {
            cout << "Пользователь с таким логином не найден" << endl;
        }
    }
}

void Chat::checkMessages() {
    if (!loggedInUser) {
        cout << "Сначала войдите в систему " << endl;
        return;
    }
    loggedInUser->showInbox();
}

void Chat::run() {
    while (true) {
        cout << "\n--- Меню ---\n";
        cout << "1. Регистрация" << endl;
        cout << "2. Вход" << endl;
        cout << "3. Отправить сообщение" << endl;
        cout << "4. Проверить сообщения" << endl;
        cout << "5. Выход из аккаунта" << endl;
        cout << "6. Выход из программы" << endl;
        cout << "Выберите действие: " << endl;

        string choice;
        cin >> choice;

        try {
            if (choice == "1") {
                registerUser();
            }
            else if (choice == "2") {
                login();
            }
            else if (choice == "3") {
                sendMessage();
            }
            else if (choice == "4") {
                checkMessages();
            }
            else if (choice == "5") {
                logout();
            }
            else if (choice == "6") {
                cout << "Выход из программы..." << endl;
                break;
            }
            else {
                cout << "Некорректный ввод. Попробуйте снова" << endl;
            }
        }
        catch (const exception& e) {
            cout << "Произошла ошибка: " << e.what() << endl;
        }
    }
}
