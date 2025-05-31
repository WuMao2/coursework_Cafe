#include "CMenuItem.hpp"
#include "CDesertItem.hpp"
#include <iostream>
#include <sstream>

std::string CDesertItem::serialize() const {
    std::ostringstream oss;
    oss << "Desert " << " " << name << " " << price << " \""
        << "\" " << (sugarFree ? "true" : "false") << " " << calories;
    return oss.str();
}

void CDesertItem::edit(const std::string& newName, double newPrice, bool isSugarFree, int newVolume) {
    name = newName;
    price = newPrice;
    sugarFree = isSugarFree;
    calories = newVolume;
}

void CDesertItem::display() const {
        std::cout << "[Desert] ID: " << id << ", Name: " << name
                  << ", Price: $" << price << ", Sugar: " 
                  << (isSugarFree() ? "Yes" : "No")
                  << ", Calories: " << calories << '\n';
}