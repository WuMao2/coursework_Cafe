#include "CSession.hpp"
#include <sstream>
#include <limits>
#include "Utils.hpp"

CSession::~CSession() {

    if (admin != nullptr) {
        delete admin;
    }
}

void CSession::endSession() {
    running = false;
    logout();
    tables.freeTable(curTableId);
    tables.saveTablesToFile("tables.txt");
}

void CSession::initialize() {
    // Load menu and orders from files
    menu.loadFromFile("menu.txt");
    orderList.loadFromFile("orders.txt");
    tables.loadTablesFromFile("tables.txt");
}

void CSession::logout() {
    if (admin != nullptr) {
      delete admin;
      admin = nullptr;
    }
    curTableId = 0;
}

bool CSession::loginAdmin() {
    // Clear existing admin session
    delete admin;
    admin = nullptr;

    std::string inputUsername, inputPassword;
    std::cout << "Enter admin username: ";
    std::getline(std::cin, inputUsername);
    std::cout << "Enter admin password: ";
    std::getline(std::cin, inputPassword);

    std::ifstream file("admins.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open admins.txt\n";
    }

    std::string fileUsername, filePassword;
    int id;
    while (file >> std::quoted(fileUsername) >> std::quoted(filePassword) >> id) {
        if (fileUsername == inputUsername && filePassword == inputPassword) {
            file.close();
            admin = new CAdmin(inputUsername, inputPassword, true, id);
        }
    }
    file.close();

    if (admin) {
        std::cout << "Admin logged in successfully.\n";
        awaitForInput();
    } else {
        std::cout << "Login failed. Please try again.\n";
        awaitForInput();
    }
    return (admin != nullptr);
}

bool CSession::isAdminLoggedIn() const {
    return (admin != nullptr);
}


CAdmin* CSession::getAdmin() {
    return admin;
}

void CSession::displayAdminStatus() {
    std::cout << "Admin " << getAdmin()->getUsername() << " is logged in with employee ID: "
              << getAdmin()->getEmployeeId() << std::endl;
    awaitForInput();
}

void CSession::orderingSequence() {
    if (curTableId == 0) {
        std::cout << "Please select a table first.\n";
        awaitForInput();
        return;
    }

    COrder order(orderList.getOrders().size() + 1, curTableId);

    while (true) {
        system(CLEAR_CMD);
        this->displayMenu();
        std::cout << "\nCurrent order:\n";
        order.printOrder();
        //remove item from order or add item to order
        std::cout << "\n=== Ordering Menu ===\n";
        std::cout << "1. Add Item to Order\n";
        std::cout << "2. Remove Item from Order\n";
        std::cout << "3. Finish Order\n";
        std::cout << "Choice: ";
        
        int choice = strictInput();
        if (choice == -1) continue;

        if (choice == 1) {
            std::cout << "Enter item ID to add: ";
            int itemId = strictInput();
            if (itemId == -1) continue;

            auto item = menu.findById(itemId);
            if (item) {
                order.addItem(item);
                std::cout << "Item added to order.\n";
            } else {
                std::cout << "Item not found.\n";
            }
        } else if (choice == 2) {
            std::cout << "Enter item ID to remove: ";
            int itemId = strictInput();
            if (itemId == -1) continue;

            order.removeItem(itemId);
            std::cout << "Item removed from order.\n";
        } else if (choice == 3) {
            break; // Finish ordering
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    system(CLEAR_CMD);
    //check if order is empty
    if (order.getOrderItems().empty()) {
        return;
    }

    order.printOrder();
    std::cout << "\nConfirm order? (y/n): ";
    std::string confirmInput;
    std::getline(std::cin, confirmInput);
    if (confirmInput.empty() || (confirmInput[0] != 'y' && confirmInput[0] != 'Y')) {
        return;
    } 
    orderList.addOrder(order);
    orderList.fixOrderIds();
    orderList.saveToFile("orders.txt");
}

void CSession::orderCheck() {
    if (curTableId == 0) {
        std::cout << "Please select a table first.\n";
        awaitForInput();
        return;
    }
    //display all orders for the current table
    system(CLEAR_CMD);
    std::cout << "Current table: " << curTableId << "\n";
    std::cout << "=== Current Orders ===\n";
    bool found = false;
    for (const auto &order : orderList.getOrders()) {
        if (order.getTableId() == curTableId) {
            order.printOrder();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No orders found for this table.\n";
    }
    awaitForInput();
}

void CSession::editMenu() {
    while (true) {
        system(CLEAR_CMD);
        this->displayMenu();
        std::cout << "\n=== Edit Menu ===\n";
        std::cout << "1. Add Food Item\n";
        std::cout << "2. Add Drink Item\n";
        std::cout << "3. Add Desert Item\n";
        std::cout << "4. Remove Item\n";
        std::cout << "5. Save and Exit\n";
        std::cout << "Choice: ";

        int choice = strictInput();
        if (choice == -1) continue;

        switch(choice) {
            case 1: {
                std::string name;
                double price;
                bool vegetarian;
                std::cout << "Enter food name: ";
                std::getline(std::cin, name);
                std::cout << "Enter price: ";
                price = strictInputDouble();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Is it vegetarian? (y/n): ";
                vegetarian = strictInputBool();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter calories: ";
                int calories = strictInput();
                if (calories == -1) continue;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                menu.addFoodItem(name, price, vegetarian, calories);
                break;
            }
            case 2: {
                std::string name;
                double price;
                bool alcoholic;
                std::cout << "Enter drink name: ";
                std::getline(std::cin, name);
                std::cout << "Enter price: ";
                price = strictInputDouble();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Is it alcoholic? (y/n): ";
                alcoholic = strictInputBool();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter volume in ml: ";
                int volume = strictInput();
                if (volume == -1) continue;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                menu.addDrinkItem(name, price, alcoholic, volume);
                break;
            }
            case 3: {
                std::string name;
                double price;
                bool sugarFree;
                std::cout << "Enter desert name: ";
                std::getline(std::cin, name);
                std::cout << "Enter price: ";
                price = strictInputDouble();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Is it sugar-free? (y/n): ";
                sugarFree = strictInputBool();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter calories: ";
                int calories = strictInput();
                if (calories == -1) continue;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                menu.addDesertItem(name, price, sugarFree, calories);
                break;
            }
            case 4: {
                std::cout << "Enter item ID to remove: ";
                int id = strictInput();
                if (id == -1) continue;
                if (!menu.removeItem(id)) {
                    std::cout << "Item not found.\n";
                    awaitForInput();
                    continue; // Go back to the menu
                }
                break;
            }
            case 5:
              menu.saveToFile("menu.txt");
              return; // Exit edit menu
            default:
              std::cout << "Invalid choice. Please try again.\n";
              awaitForInput();
        }
    }
}

void CSession::editOrders() {
    while (true) {
        system(CLEAR_CMD);
        this->displayOrders();
        std::cout << "\n=== Edit Orders ===\n";
        std::cout << "1. Remove Order\n";
        std::cout << "2. Mark Order as Finished\n";
        std::cout << "3. Save and Exit\n";
        std::cout << "Choice: ";

        int choice = strictInput();
        if (choice == -1) continue;

        switch(choice) {
            case 1: {
                std::cout << "Enter order ID to remove: ";
                int id = strictInput();
                if (id == -1) continue;
                if (!orderList.removeOrder(admin, id)) {
                    std::cout << "Order not found.\n";
                    awaitForInput();
                    continue; // Go back to the menu
                }
                break;
            }
            case 2: {
                std::cout << "Enter order ID to mark as finished: ";
                int id = strictInput();
                if (id == -1) continue;
                if (!orderList.markOrderAsFinished(id)) {
                    std::cout << "Order not found or already finished.\n";
                    awaitForInput();
                    continue; // Go back to the menu
                }
                break;
            }
            case 3:
              orderList.saveToFile("orders.txt");
              return; // Exit edit orders
            default:
              std::cout << "Invalid choice. Please try again.\n";
              awaitForInput();
        }
    }
}

void CSession::changeTable() {
    system(CLEAR_CMD);
    std::cout << "Current table ID: " << curTableId << "\n";
    tables.displayTables();

    std::cout << "Enter new table ID: ";
    int newTableId = strictInput();
    if (newTableId == -1) return;

    if (!tables.isTableOccupied(newTableId)) {
        if (curTableId != 0) {
          tables.freeTable(curTableId);
        }  
        curTableId = newTableId;
        std::cout << "Table changed successfully to ID: " << curTableId << "\n";
        tables.occupyTable(curTableId);
        tables.saveTablesToFile("tables.txt");
    } else {
        std::cout << "Table ID " << newTableId << " is not available.\n";
    }
    awaitForInput();
}

void CSession::markAsFreeTable() {
    // ask for an id to free, admins have no cur table id so dont display that
    system(CLEAR_CMD);
    tables.displayTables(admin);
    std::cout << "\nEnter table ID to free: ";
    int tableId = strictInput();
    if (tableId == -1) return;
    if (tables.isTableOccupied(tableId)) {
        tables.freeTable(tableId);
        tables.saveTablesToFile("tables.txt");
    } else {
        std::cout << "Table ID " << tableId << " is already free.\n";
    }
    awaitForInput();
}