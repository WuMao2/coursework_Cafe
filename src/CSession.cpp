#include "CSession.hpp"

CSession::~CSession() {
    if (curUser.getLoggedIn()) {
        curUser.saveChangesIntoFile();
    }
    if (admin != nullptr) {
        delete admin;
    }
}

void CSession::awaitForInput() {
    std::cout << "\nPress any key to continue...";
    std::cin.ignore();
    std::cin.get();
}

void CSession::initialize() {
    // Load menu and orders from files
    menu.loadFromFile("menu.txt");
    orderList.loadFromFile("orders.txt");
}

bool CSession::loginUser() {
    if (curUser.getLoggedIn()) {
        std::cout << "You are already logged in as " << curUser.getUsername() << ".\n";
        awaitForInput();
        return true;
    }
    std::string inputUsername, inputPassword;
    std::cout << "Enter username: ";
    std::cin >> inputUsername;
    std::cout << "Enter password: ";
    std::cin >> inputPassword;
    if (curUser.loginFromFile(inputUsername, inputPassword)) {
        std::cout << "Login successful. Welcome, " << curUser.getUsername() << "!\n";
        awaitForInput();
    } else {
        std::cout << "Login failed. Please try again.\n";
        awaitForInput();
        return false;
    }
    return curUser.getLoggedIn();
}

bool CSession::registerUser() {
    if (!curUser.getLoggedIn()) {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        if (curUser.registerIntoFile(username, password)) {
            std::cout << "Registration successful. You can now log in.\n";
            awaitForInput();
        } else {
            std::cout << "Registration failed. Please try again.\n";
            awaitForInput();
            return false;
        }
        
        return true;
    }
    return false;
}

void CSession::logout() {
    if (admin != nullptr) {
      delete admin;
      admin = nullptr;
      curUser.logout();
    } else {
      if (curUser.getLoggedIn()) {
        curUser.saveChangesIntoFile();
        curUser.logout();
      }
    }
}

bool CSession::isUserLoggedIn() const {
    return curUser.getLoggedIn();
}

bool CSession::loginAdmin() {
    // Clear existing admin session
    delete admin;
    admin = nullptr;

    std::string inputUsername, inputPassword;
    std::cout << "Enter admin username: ";
    std::cin >> inputUsername;
    std::cout << "Enter admin password: ";
    std::cin >> inputPassword;

    admin = curUser.loginAdmin(inputUsername, inputPassword);

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

CUser& CSession::getUser() {
    return curUser;
}

CAdmin* CSession::getAdmin() {
    return admin;
}

void CSession::displayUserStatus() {
    std::cout << "User " << curUser.getUsername() << " is logged in." << std::endl;
    awaitForInput();
}

void CSession::displayAdminStatus() {
    std::cout << "Admin " << getAdmin()->getUsername() << " is logged in with employee ID: "
              << getAdmin()->getEmployeeId() << std::endl;
    awaitForInput();
}

void CSession::orderingSequence() {
    std::string customerName = curUser.getUsername();
    COrder order(customerName);
    order.setId(orderList.getOrders().size() + 1);

    while (true) {
        system(CLEAR_CMD);
        this->displayMenu();
        std::cout << "\nCurrent order:\n";
        order.printOrder();
        std::cout << "Total price: " << order.getTotalPrice() << "\nEnter item ID to add to order (0 to finish): ";
        int itemId;
        std::cin >> itemId;
        
        if (itemId == 0) {
            break;
        }

        auto item = menu.findById(itemId);
        if (item) {
            order.addItem(item);
        }
    }

    order.printOrder();
    std::cout << "\nConfirm order? (y/n): ";
    char confirm;
    std::cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        return;
    } 
    orderList.addOrder(order);
}

void CSession::orderCheck() {
    std::string customerName = curUser.getUsername();
    const auto& orders = orderList.getOrders();

    for (const auto& order : orders) {
        if (order.getCustomerName() == customerName) {
            order.printOrder();
            awaitForInput();
            return;
        }
    }

    std::cout << "No orders found for user " << customerName << ".\n";
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

        int choice;
        std::cin >> choice;

        switch(choice) {
            case 1: {
                std::string name;
                double price;
                bool vegetarian;
                int calories;
                std::cout << "Enter food name: ";
                std::cin >> name;
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Is it vegetarian? (1 for yes, 0 for no): ";
                std::cin >> vegetarian;
                std::cout << "Enter calories: ";
                std::cin >> calories;
                menu.addFoodItem(name, price, vegetarian, calories);
                break;
            }
            case 2: {
                std::string name;
                double price;
                bool alcoholic;
                int volume;
                std::cout << "Enter drink name: ";
                std::cin >> name;
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Is it alcoholic? (1 for yes, 0 for no): ";
                std::cin >> alcoholic;
                std::cout << "Enter volume in ml: ";
                std::cin >> volume;
                menu.addDrinkItem(name, price, alcoholic, volume);
                break;
            }
            case 3: {
                std::string name;
                double price;
                bool sugarFree;
                int calories;
                std::cout << "Enter desert name: ";
                std::cin >> name;
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Is it sugar-free? (1 for yes, 0 for no): ";
                std::cin >> sugarFree;
                std::cout << "Enter calories: ";
                std::cin >> calories;
                menu.addDesertItem(name, price, sugarFree, calories);
                break;
            }
            case 4: {
                int id;
                std::cout << "Enter item ID to remove: ";
                std::cin >> id;
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

        int choice;
        std::cin >> choice;

        switch(choice) {
            case 1: {
                int id;
                std::cout << "Enter order ID to remove: ";
                std::cin >> id;
                if (!orderList.removeOrder(id)) {
                    std::cout << "Order not found.\n";
                    awaitForInput();
                    continue; // Go back to the menu
                }
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter order ID to mark as finished: ";
                std::cin >> id;
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