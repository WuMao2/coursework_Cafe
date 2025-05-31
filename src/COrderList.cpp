#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "COrder.hpp"
#include "COrderList.hpp"
#include "CFoodItem.hpp"
#include "CDrinkItem.hpp"
#include "CDesertItem.hpp"

void COrderList::addOrder(const COrder &order) {
    orders.push_back(order);
}

void COrderList::removeOrder(const std::string &customerName) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getCustomerName() == customerName) {
            orders.erase(it);
            fixOrderIds();
            return;
        }
    }
}

bool COrderList::markOrderAsFinished(int id) {
    for (auto &order : orders) {
        if (order.getId() == id) {
            order.markAsFinished();
            return true;
        }
    }
    return false;
}

bool COrderList::removeOrder(int id) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getId() == id) {
            orders.erase(it);
            return true;
        }
    }
    return false;
}

const std::vector<COrder>& COrderList::getOrders() const {
    return orders;
}

void COrderList::printAllOrders() const {
    for (const auto &order : orders) {
        order.printOrder();
    }
}

void COrderList::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open orders file for reading.\n";
        return;
    }

    std::string line;
    COrder* currentOrder = nullptr;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        // Check if the line is an order header (starts with a number)
        int id;
        ss >> id;

        if (!ss.fail()) {
            // It's a new order
            std::string customerName;
            double totalPrice;
            int isFinishedInt;

            ss >> customerName >> totalPrice >> isFinishedInt;

            COrder order(customerName);
            order.setId(id);
            if (isFinishedInt) order.markAsFinished();

            orders.push_back(order);
            currentOrder = &orders.back(); // save pointer to current order
        } else if (currentOrder != nullptr) {
            // It's an item line
            std::istringstream itemStream(line);
            std::string itemType;
            itemStream >> itemType;

            if (itemType == "Food") {
                int foodId, calories;
                std::string name;
                double price;
                int vegetarianInt;

                itemStream >> foodId >> name >> price >> vegetarianInt >> calories;
                auto foodItem = std::make_shared<CFoodItem>(foodId, name, price, vegetarianInt != 0, calories);
                currentOrder->addItem(foodItem);
            } else if (itemType == "Drink") {
                int drinkId, volume;
                std::string name;
                double price;
                int alcoholicInt;

                itemStream >> drinkId >> name >> price >> alcoholicInt >> volume;
                auto drinkItem = std::make_shared<CDrinkItem>(drinkId, name, price, alcoholicInt != 0, volume);
                currentOrder->addItem(drinkItem);
            } else if (itemType == "Desert") {
                int desertId, calories;
                std::string name;
                double price;
                int sugarFreeInt;

                itemStream >> desertId >> name >> price >> sugarFreeInt >> calories;
                auto desertItem = std::make_shared<CDesertItem>(desertId, name, price, sugarFreeInt != 0, calories);
                currentOrder->addItem(desertItem);
            }
        }
    }

    file.close();
}



void COrderList::saveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open orders file for writing.\n";
        return;
    }
    for (const auto &order : orders) {
        file << order.getId() << " " << order.getCustomerName() << " "
             << order.getTotalPrice() << " " << (order.isOrderFinished() ? "1" : "0") << "\n";

        for (const auto &item : order.getOrderItems()) {
            file << item->serialize() << "\n";
        }
    }
    file.close();
}

void COrderList::fixOrderIds() {
    int newId = 1;
    for (auto &order : orders) {
        order.setId(newId++);
    }
}