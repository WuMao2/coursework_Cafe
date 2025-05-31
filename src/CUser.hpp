#pragma once

#include <iostream>
#include <fstream>
#include <string>

class CAdmin;

class CUser {
    friend class CAdmin;

private:
    std::string username;
    std::string password;
    bool isLoggedIn;

public:
    CUser(const std::string& u = "Unknown Customer", const std::string& p = "", bool loggedIn = false);
    virtual ~CUser() = default;

    bool loginFromFile(const std::string& u, const std::string& p);
    bool registerIntoFile(const std::string& u, const std::string& p);
    void logout();

    CAdmin* loginAdmin(const std::string& u, const std::string& p);

    void saveChangesIntoFile();

    std::string getUsername() const;
    bool getLoggedIn() const;

};
