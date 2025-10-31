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
    cout << "����������� ������ ������������" << endl ;
    string login, password, name;

    cout << "������� �����: " << endl;
    cin >> login;

    if (findUserByLogin(login)) {
        cout << "����� ����� ��� ���������� " << endl;
        return;
    }

    cout << "������� ������: ";
    cin >> password;
    cout << "������� ���: ";
    cin.ignore();
    getline(cin, name);

    users.push_back(make_shared<User>(login, password, name));
    cout << "������������ ������� ���������������" << endl;
}

void Chat::login() {
    cout << "���� � �������" << endl;
    string login, password;
    cout << "�����: ";
    cin >> login;
    cout << "������: ";
    cin >> password;

    auto user = findUserByLogin(login);
    if (user && user->getPassword() == password) {
        loggedInUser = user;
        cout << "����� ����������, " << user->getName() << " " << endl;
    }
    else {
        cout << "�������� ����� ��� ������" << endl;
    }
}

void Chat::logout() {
    if (loggedInUser) {
        cout << "������������ " << loggedInUser->getName() << " ����� �� �������" << endl;
        loggedInUser.reset();
    }
    else {
        cout << "�� �� ����� � �������" << endl;
    }
}

void Chat::sendMessage() {
    if (!loggedInUser) {
        cout << "������� ������� � �������" << endl;
        return;
    }

    cout << "������� ����� ���������� (��� 'all' ��� ��������� ����):" << endl;
    string to;
    cin >> to;

    cout << "������� ���������: " << endl;
    cin.ignore();
    string text;
    getline(cin, text);

    if (to == "all") {
        int sentCount = 0;
        for (auto& user : users) {
            if (user->getLogin() != loggedInUser->getLogin()) {
                user->addMessage("[����� ���] " + loggedInUser->getName() + ": " + text);
                sentCount++;
            }
        }
        cout << "��������� ���������� " << sentCount << " �������������" << endl;
    }
    else {
        auto user = findUserByLogin(to);
        if (user) {
            user->addMessage("[������] " + loggedInUser->getName() + ": " + text);
            cout << "��������� ���������� ������������ " << user->getName() << "." << endl;
        }
        else {
            cout << "������������ � ����� ������� �� ������" << endl;
        }
    }
}

void Chat::checkMessages() {
    if (!loggedInUser) {
        cout << "������� ������� � ������� " << endl;
        return;
    }
    loggedInUser->showInbox();
}

void Chat::run() {
    while (true) {
        cout << "\n--- ���� ---\n";
        cout << "1. �����������" << endl;
        cout << "2. ����" << endl;
        cout << "3. ��������� ���������" << endl;
        cout << "4. ��������� ���������" << endl;
        cout << "5. ����� �� ��������" << endl;
        cout << "6. ����� �� ���������" << endl;
        cout << "�������� ��������: " << endl;

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
                cout << "����� �� ���������..." << endl;
                break;
            }
            else {
                cout << "������������ ����. ���������� �����" << endl;
            }
        }
        catch (const exception& e) {
            cout << "��������� ������: " << e.what() << endl;
        }
    }
}
