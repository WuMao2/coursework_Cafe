#include "CUser.hpp"
#include "CAdmin.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

CUser::CUser(const std::string& u, const std::string& p, bool s)
    : username(u), password(p), isLoggedIn(s) {}

bool CUser::loginFromFile(const std::string& u, const std::string& p) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open users.txt\n";
        return false;
    }

    std::string fileUsername, filePassword;
    while (file >> std::quoted(fileUsername) >> std::quoted(filePassword)) {
        if (fileUsername == u && filePassword == p) {
            username = u;
            password = p;
            isLoggedIn = true;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

CAdmin* CUser::loginAdmin(const std::string& u, const std::string& p) {
    std::ifstream file("admins.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open admins.txt\n";
        return nullptr;
    }

    std::string fileUsername, filePassword;
    int id;
    while (file >> std::quoted(fileUsername) >> std::quoted(filePassword) >> id) {
        if (fileUsername == u && filePassword == p) {
            username = u;
            password = p;
            isLoggedIn = true;
            file.close();
            return new CAdmin(u, p, true, id);
        }
    }
    file.close();
    return nullptr;
}

bool CUser::registerIntoFile(const std::string& u, const std::string& p) {
    std::ifstream inFile("users.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open users.txt for reading.\n";
        return false;
    }

    std::string existingUsername, existingPassword;
    while (inFile >> std::quoted(existingUsername) >> std::quoted(existingPassword)) {
        if (existingUsername == u) {
            std::cout << "Username already exists. Please choose a different one.\n";
            inFile.close();
            return false;
        }
    }
    inFile.close();

    std::ofstream outFile("users.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open users.txt for writing.\n";
        return false;
    }

    outFile << std::quoted(u) << ' ' << std::quoted(p) << '\n';
    outFile.close();
    return true;
}

void CUser::saveChangesIntoFile() {
    if (!isLoggedIn) return;

    std::ifstream inFile("users.txt");
    std::ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        inFile.close();
        tempFile.close();
        std::cerr << "Unable to open files for updating user data.\n";
        return;
    }

    std::string fileUsername, filePassword;
    while (inFile >> std::quoted(fileUsername) >> std::quoted(filePassword)) {
        if (fileUsername == username && filePassword == password) {
            tempFile << std::quoted(username) << ' ' << std::quoted(password) << '\n';
        } else {
            tempFile << std::quoted(fileUsername) << ' ' << std::quoted(filePassword) << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    std::remove("users.txt");
    std::rename("temp.txt", "users.txt");
}

void CUser::logout() {
    username = "Unknown Customer";
    password.clear();
    isLoggedIn = false;
}

std::string CUser::getUsername() const {
    return username;
}

bool CUser::getLoggedIn() const {
    return isLoggedIn;
}