#pragma once
#include <memory>
#include <vector>
#include <string>
#include "User.h"

class Chat {
private:
    std::vector<std::shared_ptr<User>> users;
    std::shared_ptr<User> loggedInUser = nullptr;

    std::shared_ptr<User> findUserByLogin(const std::string& login);

public:
    void registerUser();
    void login();
    void logout();
    void sendMessage();
    void checkMessages();
    void run();
};
