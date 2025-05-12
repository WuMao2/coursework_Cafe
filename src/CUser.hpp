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
    int points;

public:
    // Constructors & Destructor
    CUser(const std::string& u = "Unknown Customer", const std::string& p = "", bool loggedIn = false);
    virtual ~CUser() = default;

    // Login/Register
    virtual void loginFromFile(const std::string& u, const std::string& p);
    virtual void registerIntoFile(const std::string& u, const std::string& p);
    virtual void logout();

    // Admin login (returns dynamically allocated admin)
    CAdmin* loginAdmin(const std::string& u, const std::string& p);

    // Data persistence
    void saveChangesIntoFile();

    // Getters
    std::string getUsername() const;
    bool getLoggedIn() const;
    int getPoints() const;

    // Setters
    void setPoints(int value);
};
