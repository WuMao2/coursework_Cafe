#pragma once
#include "CMenuItem.hpp"
#include <iostream>
#include <sstream>

class CDesertItem : public CMenuItem {
private:
    int calories;
    bool sugarFree;

public:
    CDesertItem(int id, const std::string& name, double price, bool sugarFree, int calories)
        : CMenuItem(id, name, price), sugarFree(sugarFree), calories(calories) {}

    std::string serialize() const override;

    std::string getType() const override { return "Desert"; }
    void display() const override;
    void edit(const std::string &newName, double newPrice, bool sugarFree, int newVolume);
    bool isSugarFree() const { return sugarFree; }
};