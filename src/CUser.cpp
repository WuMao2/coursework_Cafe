#include "CUser.hpp"
#include "CAdmin.hpp"
#include <iostream>
#include <fstream>

CUser::CUser(const std::string& u, const std::string& p, bool s)
    : username(u), password(p), isLoggedIn(s) {}

bool CUser::loginFromFile(const std::string& u, const std::string& p) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open users.txt\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t firstSpace = line.find(' ');
        std::string fileUsername = line.substr(0, firstSpace);
        std::string filePassword = line.substr(firstSpace + 1);

        if (fileUsername == u && filePassword == p) {
            username = u;
            password = p;
            isLoggedIn = true;
            return true;
        }
    }
    return false;
}

CAdmin* CUser::loginAdmin(const std::string& u, const std::string& p) {
    std::ifstream file("admins.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open admins.txt\n";
        return nullptr;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t firstSpace = line.find(' ');
        size_t secondSpace = line.find(' ', firstSpace + 1);
        size_t thirdSpace = line.find(' ', secondSpace + 1);

        std::string fileUsername = line.substr(0, firstSpace);
        std::string filePassword = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
        int id = std::stoi(line.substr(secondSpace + 1, thirdSpace - secondSpace - 1));

        if (fileUsername == u && filePassword == p) {
            username = u;
            password = p;
            isLoggedIn = true;
            id = 0;
            return new CAdmin(u, p, true, id);
        }
    }

    return nullptr;
}

bool CUser::registerIntoFile(const std::string& u, const std::string& p) {
    std::ifstream inFile("users.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open users.txt for reading.\n";
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        size_t firstSpace = line.find(' ');
        std::string existingUsername = line.substr(0, firstSpace);
        if (existingUsername == u) {
            std::cout << "Username already exists. Please choose a different one.\n";
            return false;
        }
    }
    inFile.close();

    std::ofstream outFile("users.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open users.txt for writing.\n";
        return false;
    }

    outFile << u << " " << p << '\n';
    outFile.close();
    return true;
}

void CUser::saveChangesIntoFile() {
    if (!isLoggedIn) return;

    std::ifstream inFile("users.txt");
    std::ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        std::cerr << "Unable to open files for updating user data.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        size_t firstSpace = line.find(' ');
        size_t secondSpace = line.find(' ', firstSpace + 1);

        std::string fileUsername = line.substr(0, firstSpace);
        std::string filePassword = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);

        if (fileUsername == username && filePassword == password) {
            tempFile << username << " " << password << " " << '\n';
        } else {
            tempFile << line << '\n';
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