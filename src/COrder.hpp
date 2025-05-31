#pragma once
#include <vector>
#include <string>
#include "CMenu.hpp"

class COrder {
private:
    int id = 0;
    double totalPrice = 0.0;
    std::string customerName;
    bool isFinished = false;
    std::vector<std::shared_ptr<CMenuItem>> orderItems;
public:
    COrder(const std::string &customerName) : customerName(customerName) {}

    void addItem(const std::shared_ptr<CMenuItem> &item);
    void removeItem(int id);
    void markAsFinished() { isFinished = true; }

    void setId(int newId);
    int getId() const { return id; }
    double getTotalPrice() const { return totalPrice; }
    const std::string &getCustomerName() const { return customerName; }
    bool isOrderFinished() const { return isFinished; }
    const std::vector<std::shared_ptr<CMenuItem>> &getOrderItems() const { return orderItems; }

    void printOrder() const;
};