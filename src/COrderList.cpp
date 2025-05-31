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
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int id;
        std::string customerName;
        double totalPrice;
        bool isFinished;

        ss >> id >> customerName >> totalPrice >> isFinished;

        COrder order(customerName);
        order.setId(id);
        if (isFinished) {
            order.markAsFinished();
        }

        // Read items for the order
        std::string itemLine;
        while (std::getline(ss, itemLine) && !itemLine.empty()) {
            std::istringstream itemStream(itemLine);
            std::string itemType;
            itemStream >> itemType;

            if (itemType == "Food") {
                int foodId, calories;
                std::string name;
                double price;
                bool vegetarian;

                itemStream >> foodId >> name >> price >> vegetarian >> calories;
                auto foodItem = std::make_shared<CFoodItem>(foodId, name, price, vegetarian, calories);
                order.addItem(foodItem);
            } else if (itemType == "Drink") {
                int drinkId, volume;
                std::string name;
                double price;
                bool alcoholic;

                itemStream >> drinkId >> name >> price >> alcoholic >> volume;
                auto drinkItem = std::make_shared<CDrinkItem>(drinkId, name, price, alcoholic, volume);
                order.addItem(drinkItem);
            } else if (itemType == "Desert") {
                int desertId, calories;
                std::string name;
                double price;
                bool sugarFree;

                itemStream >> desertId >> name >> price >> sugarFree >> calories;
                auto desertItem = std::make_shared<CDesertItem>(desertId, name, price, sugarFree, calories);
                order.addItem(desertItem);
            }
        }

        orders.push_back(order);
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