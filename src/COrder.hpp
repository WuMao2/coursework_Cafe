#pragma once
#include <vector>
#include <string>
#include "CMenu.hpp"

class COrder {
private:
    int id = 0;
    double totalPrice = 0.0;
    int tableId;
    bool isFinished = false;
    std::vector<std::shared_ptr<CMenuItem>> orderItems;
public:
    COrder(int id, int tableId) : id(id), tableId(tableId) {}

    void addItem(const std::shared_ptr<CMenuItem> &item);
    void removeItem(int id);
    void markAsFinished() { isFinished = true; }

    void setId(int newId);
    int getTableId() const { return tableId; }
    int getId() const { return id; }
    double getTotalPrice() const { return totalPrice; }
    bool isOrderFinished() const { return isFinished; }
    const std::vector<std::shared_ptr<CMenuItem>> &getOrderItems() const { return orderItems; }

    void printOrder() const;
};