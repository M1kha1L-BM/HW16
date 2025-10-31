#include "User.h"
#include <iostream>
using namespace std;

User::User(const std::string& login, const std::string& password, const std::string& name)
    : login(login), password(password), name(name) {}

std::string User::getLogin() const { return login; }
std::string User::getPassword() const { return password; }
std::string User::getName() const { return name; }

void User::addMessage(const std::string& msg) {
    inbox.push_back(msg);
}

void User::showInbox() {
    if (inbox.empty()) {
        cout << "Нет новых сообщений " << endl;
        return;
    }

    cout << "--- Сообщения для " << name << endl;
    for (const auto& msg : inbox)
        cout << msg << endl;

    inbox.clear();
}
