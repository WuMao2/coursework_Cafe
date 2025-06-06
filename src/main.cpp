#include <iostream>
#include <string>
#include <sstream>
#include "CSession.hpp"
#include "Utils.hpp"


int main() {
    CSession session;
    session.initialize();

    while (session.isRunning()) {
        system(CLEAR_CMD);
        if (!session.isAdminLoggedIn()) {
            std::cout << "Current table: " << session.getCurTableId() << "\n";
            std::cout << "\n=== Main Menu ===\n";
            std::cout << "1. Make an Order\n";
            std::cout << "2. Check Orders\n";
            std::cout << "3. Change Table\n";
            std::cout << "4. Login as Admin\n";
            std::cout << "5. Exit\n";
            std::cout << "Choice: ";

            int choice = strictInput();
            if (choice == -1) continue;

            switch (choice) {
                case 1:
                  session.orderingSequence();
                  break;
                case 2:
                  session.orderCheck();
                  break;
                case 3:
                  session.changeTable();
                  break;
                case 4:
                  session.loginAdmin();
                  break;
                case 5:
                  session.endSession();
                  break;
                default:
                  std::cout << "Invalid choice.\n";
                  awaitForInput();
            }
        } else {
            std::cout << "\n=== Admin Menu ===\n";
            std::cout << "1. Edit Menu\n";
            std::cout << "2. Edit Orders\n";
            std::cout << "3. Check Status\n";
            std::cout << "4, Free Table\n";
            std::cout << "5. Logout\n";
            std::cout << "6. Exit\n";
            std::cout << "Choice: ";

            int choice = strictInput();
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
                  session.markAsFreeTable();
                  break;
                case 5:
                  session.logout();
                  break;
                case 6:
                  session.endSession();
                  break;
                default:
                    std::cout << "Invalid choice.\n";
                    awaitForInput();
            }
        }
    }

    std::cout << "Exiting application. Goodbye!\n";
    awaitForInput();
    return 0;
}