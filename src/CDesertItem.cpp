#include "CMenuItem.hpp"
#include "CDesertItem.hpp"
#include <iostream>
#include <sstream>

std::string CDesertItem::serialize() const {
    std::ostringstream oss;
    oss << "Desert " << id << " " << std::quoted(name) << " " << price << " " << (sugarFree ? "true" : "false") << " " << calories;
    return oss.str();
}

void CDesertItem::edit(const std::string& newName, double newPrice, bool isSugarFree, int newVolume) {
    name = newName;
    price = newPrice;
    sugarFree = isSugarFree;
    calories = newVolume;
}

void CDesertItem::display() const {
    std::cout << std::left << std::setw(10) << "[Desert]"
              << "ID: "       << std::setw(4)  << id
              << "Name: "     << std::setw(20) << name
              << "Price: $"   << std::right << std::fixed << std::setprecision(2) << std::setw(6) << price << "  "
              << std::left
              << "Sugar-free: " << std::setw(3) << (isSugarFree() ? "Yes" : "No") << "  "
              << "Calories: "   << calories << '\n';
}