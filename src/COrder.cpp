#include <vector>
#include <string>
#include "CMenu.hpp"
#include "COrder.hpp"
#include <iostream>

void COrder::addItem(const std::shared_ptr<CMenuItem> &item) {
    orderItems.push_back(item);
    totalPrice += item->getPrice();
}
void COrder::removeItem(int id) {
    for (auto it = orderItems.begin(); it != orderItems.end(); ++it) {
        if ((*it)->getId() == id) {
            totalPrice -= (*it)->getPrice();
            orderItems.erase(it);
            return;
        }
    }
}

void COrder::printOrder() const {
    std::cout << id << ". Order for " << customerName << ":\n";
    for (const auto &item : orderItems) {
        item->display();
    }
    std::cout << "Total Price: $" << totalPrice << "\n";
    std::cout << "Order Status: " << (isFinished ? "Finished" : "In Progress") << "\n";
}

void COrder::setId(int id) {
    this->id = id;
}