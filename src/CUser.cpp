#include "CUser.hpp"
#include "CAdmin.hpp"

#include <iostream>
#include <fstream>

CUser::CUser(const std::string& u, const std::string& p, bool s)
    : username(u), password(p), isLoggedIn(s), points(0) {}

void CUser::loginFromFile(const std::string& u, const std::string& p) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open users.txt\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t firstSpace = line.find(' ');
        size_t secondSpace = line.find(' ', firstSpace + 1);
        size_t thirdSpace = line.find(' ', secondSpace + 1);

        std::string fileUsername = line.substr(0, firstSpace);
        std::string filePassword = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
        int filePoints = std::stoi(line.substr(secondSpace + 1, thirdSpace - secondSpace - 1));

        if (fileUsername == u && filePassword == p) {
            username = u;
            password = p;
            isLoggedIn = true;
            points = filePoints;
            std::cout << "Login successful!\n";
            return;
        }
    }

    std::cout << "Login failed!\n";
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
            std::cout << "Admin login successful!\n";
            return new CAdmin(u, p, true, id);
        }
    }

    std::cout << "Admin login failed!\n";
    return nullptr;
}

void CUser::registerIntoFile(const std::string& u, const std::string& p) {
    std::ifstream inFile("users.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open users.txt for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        size_t firstSpace = line.find(' ');
        std::string existingUsername = line.substr(0, firstSpace);
        if (existingUsername == u) {
            std::cout << "Username already exists. Please choose a different one.\n";
            return;
        }
    }
    inFile.close();

    std::ofstream outFile("users.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open users.txt for writing.\n";
        return;
    }

    outFile << u << " " << p << " " << 0 << '\n';
    std::cout << "User registered successfully!\n";
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
            tempFile << username << " " << password << " " << points << '\n';
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
    std::cout << "Logged out successfully.\n";
}

std::string CUser::getUsername() const {
    return username;
}

bool CUser::getLoggedIn() const {
    return isLoggedIn;
}

int CUser::getPoints() const {
    return points;
}

void CUser::setPoints(int value) {
    points = value;
}
