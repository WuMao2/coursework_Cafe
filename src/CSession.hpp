#pragma once
#include "CAdmin.hpp"
#include "CMenu.hpp"
#include "COrderList.hpp"
#include "COrder.hpp"
#include "CTables.hpp"

#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

class CSession {
private:
    int curTableId = 0;
    CAdmin* admin = nullptr;
    bool running = true;
    CMenu menu;
    COrderList orderList;
    CTables tables;

public:
    CSession() = default;
    ~CSession();

    void initialize();

    // Admin session management
    bool loginAdmin();
    bool isAdminLoggedIn() const;
    void logout();

    void orderingSequence();
    void orderCheck();
    void changeTable();

    void markAsFreeTable();
    void editMenu();
    void editOrders();
    // Access to current session entities
    int getCurTableId() const { return curTableId; }
    CAdmin *getAdmin();
    void displayAdminStatus();
    void displayMenu() { menu.displayMenu(); }
    void displayOrders() { orderList.printAllOrders(); }

    bool isRunning() const { return running; }
    void endSession() { running = false;  }
};
