#pragma once

#include "CUser.hpp"
#include "CAdmin.hpp"

class CSession {
private:
    CUser curUser;
    CAdmin* admin = nullptr;

public:
    CSession() = default;
    ~CSession();

    // User session management
    bool loginUser(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    void logoutUser();
    bool isUserLoggedIn() const;

    // Admin session management
    bool loginAdmin(const std::string& username, const std::string& password);
    void logoutAdmin();
    bool isAdminLoggedIn() const;

    // Access to current session entities
    CUser& getUser();
    CAdmin *getAdmin();
    void displayUserStatus();
};
