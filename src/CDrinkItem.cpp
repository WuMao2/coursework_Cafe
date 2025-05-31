#include "CMenuItem.hpp"
#include "CDrinkItem.hpp"
#include <iostream>
#include <sstream>

std::string CDrinkItem::serialize() const {
    std::ostringstream oss;
    oss << "Drink " << id << " " << name << " " << price << " \""
        << "\" " << (alcoholic ? "true" : "false") << " " << volume;
    return oss.str();
}

void CDrinkItem::edit(const std::string& newName, double newPrice, bool isAlcoholic, int newVolume) {
    name = newName;
    price = newPrice;
    alcoholic = isAlcoholic;
    volume = newVolume;
}

void CDrinkItem::display() const {
        std::cout << "[Drink] ID: " << id << ", Name: " << name
                  << ", Price: $" << price << ", Alc: " 
                  << (isAlcoholic() ? "Yes" : "No")
                  << ", Calories: " << volume << '\n';
}