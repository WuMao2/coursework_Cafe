#pragma once
#include "CMenuItem.hpp"
#include <iostream>
#include <sstream>

class CDrinkItem : public CMenuItem {
private:
    int volume;
    bool alcoholic;

public:
    CDrinkItem(int id, const std::string& name, double price, bool alcoholic, int volume)
        : CMenuItem(id, name, price), alcoholic(alcoholic), volume(volume) {}

    std::string serialize() const override;

    std::string getType() const override { return "Drink"; }
    void display() const override;
    void edit(const std::string &newName, double newPrice, bool isAlcoholic, int newVolume);
    bool isAlcoholic() const { return alcoholic; }
};