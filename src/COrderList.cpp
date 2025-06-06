#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "COrder.hpp"
#include "COrderList.hpp"
#include "CFoodItem.hpp"
#include "CDrinkItem.hpp"
#include "CDesertItem.hpp"

void COrderList::addOrder(const COrder &order) {
    orders.push_back(order);
}

void COrderList::removeOrder(const int tableId) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getTableId() == tableId) {
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

bool COrderList::removeOrder(CAdmin* admin, int id) {
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
        int id;

        // Try parsing the first token as int (order ID)
        if (ss >> id) {
          int tableId;
          double totalPrice;
          int isFinishedInt;

          ss >> tableId >> totalPrice >> isFinishedInt;

          COrder order(id, tableId);
          if (isFinishedInt)
            order.markAsFinished();

          orders.push_back(order);
          currentOrder = &orders.back();
        } else if (currentOrder != nullptr) {
            // Parse item line
            std::istringstream itemStream(line);
            std::string itemType;
            itemStream >> itemType;

            if (itemType == "Food") {
                int foodId, calories;
                std::string name, vegToken;
                double price;
                bool isVeg;

                itemStream >> foodId >> std::quoted(name) >> price >> vegToken >> calories;

                isVeg = (vegToken == "true" || vegToken == "1");

                auto foodItem = std::make_shared<CFoodItem>(foodId, name, price, isVeg, calories);
                currentOrder->addItem(foodItem);
            } else if (itemType == "Drink") {
                int drinkId, volume;
                std::string name, alcToken;
                double price;
                bool isAlcoholic;

                itemStream >> drinkId >> std::quoted(name) >> price >> alcToken >> volume;

                isAlcoholic = (alcToken == "true" || alcToken == "1");

                auto drinkItem = std::make_shared<CDrinkItem>(drinkId, name, price, isAlcoholic, volume);
                currentOrder->addItem(drinkItem);
            } else if (itemType == "Desert") {
                int desertId, calories;
                std::string name, sugarToken;
                double price;
                bool isSugarFree;

                itemStream >> desertId >> std::quoted(name) >> price >> sugarToken >> calories;

                isSugarFree = (sugarToken == "true" || sugarToken == "1");

                auto desertItem = std::make_shared<CDesertItem>(desertId, name, price, isSugarFree, calories);
                currentOrder->addItem(desertItem);
            } else {
                std::cerr << "Unknown item type: " << itemType << "\n";
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
        file << order.getId() << " " << order.getTableId() << " "
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