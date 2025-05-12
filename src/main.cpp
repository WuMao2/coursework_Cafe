#include <iostream>
#include <limits>
#include "CUser.hpp"
#include "CAdmin.hpp"
#include "CSession.hpp"



int main() {
    CSession session;

    bool running = true;
    while (running) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Login as User\n";
        std::cout << "2. Register User\n";
        std::cout << "3. Logout User\n";
        std::cout << "4. Login as Admin\n";
        std::cout << "5. Logout Admin\n";
        std::cout << "6. Display Status\n";
        std::cout << "7. Exit\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::string username, password;

        switch (choice) {
            case 1:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (session.loginUser(username, password)) {
                    std::cout << "User logged in successfully!\n";
                } else {
                    std::cout << "Login failed!\n";
                }
                break;
            case 2:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (session.registerUser(username, password)) {
                    std::cout << "User registered successfully!\n";
                }
                break;
            case 3:
                session.logoutUser();
                break;
            case 4:
                std::cout << "Enter admin username: ";
                std::cin >> username;
                std::cout << "Enter admin password: ";
                std::cin >> password;
                if (session.loginAdmin(username, password)) {
                    std::cout << "Admin logged in successfully!\n";
                } else {
                    std::cout << "Admin login failed!\n";
                }
                break;
            case 5:
                session.logoutAdmin();
                break;
            case 6:
                session.displayUserStatus();
                break;
            case 7:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}