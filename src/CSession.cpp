#include "CSession.hpp"
#include <sstream>
#include <limits>

CSession::~CSession() {
    if (curUser.getLoggedIn()) {
        curUser.saveChangesIntoFile();
    }
    if (admin != nullptr) {
        delete admin;
    }
}

void CSession::awaitForInput() {
    std::cout << "\nPress Enter to continue...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void CSession::initialize() {
    // Load menu and orders from files
    menu.loadFromFile("menu.txt");
    orderList.loadFromFile("orders.txt");
}

int CSession::strictInput() {
    std::string input;
    int choice;

    // Clear previous errors (if any)
    std::cin.clear();

    std::getline(std::cin, input);

    std::stringstream ss(input);
    if (ss >> choice && ss.eof()) {
        return choice;
    } else {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        awaitForInput();
        return -1;
    }
}

double CSession::strictInputDouble() {
    std::string input;
    double value;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    if (ss >> value && ss.eof()) {
        return value;
    } else {
        std::cout << "Invalid input. Please enter a valid number." << std::endl;
        awaitForInput();
        return -1;
    }
}

bool CSession::strictInputBool() {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        return false; // Default to false if no input
    }

    char firstChar = input[0];
    if (firstChar == 'y' || firstChar == 'Y') {
        return true;
    } else if (firstChar == 'n' || firstChar == 'N') {
        return false;
    } else {
        std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        return strictInputBool(); // Retry
    }
}

bool CSession::loginUser() {
    if (curUser.getLoggedIn()) {
        std::cout << "You are already logged in as " << curUser.getUsername() << ".\n";
        awaitForInput();
        return true;
    }
    std::string inputUsername, inputPassword;
    std::cout << "Enter username: ";
    std::getline(std::cin, inputUsername);
    std::cout << "Enter password: ";
    std::getline(std::cin, inputPassword);
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
        std::getline(std::cin, username);
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
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
    std::getline(std::cin, inputUsername);
    std::cout << "Enter admin password: ";
    std::getline(std::cin, inputPassword);

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

        int itemId = strictInput();
        if (itemId == -1) continue;

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
    std::string customerName = curUser.getUsername();
    const auto& orders = orderList.getOrders();

    bool found = false;

    for (const auto& order : orders) {
        if (order.getCustomerName() == customerName) {
            order.printOrder();
            std::cout << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No orders found for user " << customerName << ".\n";
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
                if (!orderList.removeOrder(id)) {
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
