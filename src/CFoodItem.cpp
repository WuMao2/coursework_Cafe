#include "CMenuItem.hpp"
#include "CFoodItem.hpp"
#include <iostream>
#include <sstream>

std::string CFoodItem::serialize() const {
    std::ostringstream oss;
    oss << "Food " << id << " " << name << " " << price << (vegetarian ? "true" : "false") << " " << calories;
    return oss.str();
}

void CFoodItem::edit(const std::string& newName, double newPrice, bool isVegetarian, int newCalories) {
    name = newName;
    price = newPrice;
    vegetarian = isVegetarian;
    calories = newCalories;
}

void CFoodItem::display() const {
        std::cout << "[Food] ID: " << id << ", Name: " << name
                  << ", Price: $" << price << ", Veg: " 
                  << (isVegetarian() ? "Yes" : "No")
                  << ", Calories: " << calories << '\n';
}