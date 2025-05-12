#include "CSession.hpp"

CSession::~CSession() {
    if (curUser.getLoggedIn()) {
        curUser.saveChangesIntoFile();
    }
    if (admin != nullptr) {
        delete admin;
    }
}

bool CSession::loginUser(const std::string& username, const std::string& password) {
    curUser.loginFromFile(username, password);
    return curUser.getLoggedIn();
}

bool CSession::registerUser(const std::string& username, const std::string& password) {
    if (!curUser.getLoggedIn()) {
        curUser.registerIntoFile(username, password);
        return true;
    }
    return false;
}

void CSession::logoutUser() {
    if (curUser.getLoggedIn()) {
        curUser.saveChangesIntoFile();
        curUser.logout();
    }
}

bool CSession::isUserLoggedIn() const {
    return curUser.getLoggedIn();
}

bool CSession::loginAdmin(const std::string& username, const std::string& password) {
    // Clear existing admin session
    delete admin;
    admin = nullptr;

    admin = curUser.loginAdmin(username, password);
    return (admin != nullptr);
}

void CSession::logoutAdmin() {
    if (admin != nullptr) {
        delete admin;
        admin = nullptr;
        curUser.logout();
    }
}

bool CSession::isAdminLoggedIn() const {
    return (admin != nullptr);
}

CUser& CSession::getUser() {
    return curUser;
}

CAdmin* CSession::getAdmin() {
    return admin;
}

void CSession::displayUserStatus() {
    if (isUserLoggedIn()) {
        std::cout << "User " << getUser().getUsername() << " is logged in with "
                  << getUser().getPoints() << " points." << std::endl;
    } else {
        std::cout << "No user is logged in." << std::endl;
    }

    if (isAdminLoggedIn()) {
        std::cout << "Admin " << getAdmin()->getUsername() << " is logged in." << std::endl;
    } else {
        std::cout << "No admin is logged in." << std::endl;
    }
}