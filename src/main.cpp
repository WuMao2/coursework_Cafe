#include <iostream>
#include <string>
#include <sstream>
#include "CUser.hpp"
#include "CAdmin.hpp"
#include "CSession.hpp"
#include "CMenu.hpp"
#include "CMenuItem.hpp"
#include "CFoodItem.hpp"
#include "CDrinkItem.hpp"
#include "CDesertItem.hpp"
#include "COrder.hpp"
#include "COrderList.hpp"

int main() {
    CSession session;
    session.initialize();

    while (session.isRunning()) {
        system(CLEAR_CMD);
        if (!session.isUserLoggedIn() && !session.isAdminLoggedIn()) {
            std::cout << "\n=== Main Menu ===\n";
            std::cout << "1. Login as User\n";
            std::cout << "2. Register as User\n";
            std::cout << "3. Login as Admin\n";
            std::cout << "4. Exit\n";
            std::cout << "Choice: ";

            int choice = session.strictInput();
            if (choice == -1) continue;

            switch (choice) {
                case 1:
                    session.loginUser();
                    break;
                case 2:
                    session.registerUser();
                    break;
                case 3:
                    session.loginAdmin();
                    break;
                case 4:
                    session.endSession();
                    break;
                default:
                    std::cout << "Invalid choice.\n";
                    session.awaitForInput();
            }
        } else if (session.isUserLoggedIn() && !session.isAdminLoggedIn()) {
            std::cout << "\n=== User Menu ===\n";
            std::cout << "1. Make an Order\n";
            std::cout << "2. Check Order\n";
            std::cout << "3. Check Status\n";
            std::cout << "4. Logout\n";
            std::cout << "5. Exit\n";
            std::cout << "Choice: ";

            int choice = session.strictInput();
            if (choice == -1) continue;

            switch (choice) {
                case 1:
                  session.orderingSequence();
                  break;
                case 2:
                  session.orderCheck();
                  break;
                case 3:
                  session.displayUserStatus();
                  break;
                case 4:
                  session.logout();
                  break;
                case 5:
                  session.endSession();
                  break;
                default:
                    std::cout << "Invalid choice.\n";
                    session.awaitForInput();
            }
        } else if (session.isAdminLoggedIn()) {
            std::cout << "\n=== Admin Menu ===\n";
            std::cout << "1. Edit Menu\n";
            std::cout << "2. Edit Orders\n";
            std::cout << "3. Check Status\n";
            std::cout << "4. Logout\n";
            std::cout << "5. Exit\n";
            std::cout << "Choice: ";

            int choice = session.strictInput();
            if (choice == -1) continue;

            switch (choice) {
                case 1:
                  session.editMenu();
                  break;
                case 2:
                  session.editOrders();
                  break;
                case 3:
                  session.displayAdminStatus();
                  break;
                case 4:
                  session.logout();
                  break;
                case 5:
                  session.endSession();
                  break;
                default:
                    std::cout << "Invalid choice.\n";
                    session.awaitForInput();
            }
        }
    }

    std::cout << "Exiting application. Goodbye!\n";
    session.awaitForInput();
    return 0;
}