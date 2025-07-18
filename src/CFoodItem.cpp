#include "CMenuItem.hpp"
#include "CFoodItem.hpp"
#include <iostream>
#include <sstream>

std::string CFoodItem::serialize() const {
    std::ostringstream oss;
    oss << "Food " << id << " " << std::quoted(name) << " " << price << " " << (vegetarian ? "true" : "false") << " " << calories;
    return oss.str();
}

void CFoodItem::edit(const std::string& newName, double newPrice, bool isVegetarian, int newCalories) {
    name = newName;
    price = newPrice;
    vegetarian = isVegetarian;
    calories = newCalories;
}

void CFoodItem::display() const {
    std::cout << std::left << std::setw(10) << "[Desert]"
              << "ID: "       << std::setw(4)  << id
              << "Name: "     << std::setw(20) << name
              << "Price: $"   << std::right << std::fixed << std::setprecision(2) << std::setw(6) << price << "  "
              << std::left
              << "Vegeterian: " << std::setw(3) << (isVegetarian() ? "Yes" : "No") << "  "
              << "Calories: "   << calories << '\n';
}