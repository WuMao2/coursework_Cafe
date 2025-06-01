#include "CMenuItem.hpp"
#include "CDrinkItem.hpp"
#include <iostream>
#include <sstream>

std::string CDrinkItem::serialize() const {
    std::ostringstream oss;
    oss << "Drink " << id << " " << std::quoted(name) << " " << price << " " << (alcoholic ? "true" : "false") << " " << volume;
    return oss.str();
}

void CDrinkItem::edit(const std::string& newName, double newPrice, bool isAlcoholic, int newVolume) {
    name = newName;
    price = newPrice;
    alcoholic = isAlcoholic;
    volume = newVolume;
}

void CDrinkItem::display() const {
    std::cout << std::left << std::setw(10) << "[Drink]"
              << "ID: "       << std::setw(4)  << id
              << "Name: "     << std::setw(20) << name
              << "Price: $"   << std::right << std::fixed << std::setprecision(2) << std::setw(6) << price << "  "
              << std::left
              << "Alocoholic: " << std::setw(3) << (isAlcoholic() ? "Yes" : "No") << "  "
              << "Volume: "   << volume << " ml\n";
}