#pragma once
#include "CMenuItem.hpp"
#include <iostream>
#include <sstream>

class CFoodItem : public CMenuItem {
private:
    bool vegetarian;
    int calories;

public:
    CFoodItem(int id, const std::string& name, double price, bool vegetarian, int calories)
        : CMenuItem(id, name, price), vegetarian(vegetarian), calories(calories) {}

    std::string serialize() const override;

    std::string getType() const override { return "Food"; }
    void display() const override;
    void edit(const std::string &newName, double newPrice, bool isVegetarian, int newCalories);
    bool isVegetarian() const { return vegetarian; }
  };