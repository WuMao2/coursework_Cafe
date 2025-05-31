#pragma once
#include "CUser.hpp"
#include "CAdmin.hpp"
#include "CMenu.hpp"
#include "COrderList.hpp"
#include "COrder.hpp"

#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

class CSession {
private:
    CUser curUser;
    CAdmin* admin = nullptr;
    bool running = true;
    CMenu menu;
    COrderList orderList;

public:
    CSession() = default;
    ~CSession();

    void initialize();
    void awaitForInput();
    int strictInput();
    // User session management
    bool loginUser();
    bool registerUser();
    void logout();
    bool isUserLoggedIn() const;

    // Admin session management
    bool loginAdmin();
    bool isAdminLoggedIn() const;

    void orderingSequence();
    void orderCheck();

    void editMenu();
    void editOrders();
    // Access to current session entities
    CUser& getUser();
    CAdmin *getAdmin();
    void displayUserStatus();
    void displayAdminStatus();
    void displayMenu() { menu.displayMenu(); }
    void displayOrders() { orderList.printAllOrders(); }

    bool isRunning() const { return running; }
    void endSession() { running = false;  }
};
