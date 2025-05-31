#pragma once
#include <memory>
#include <string>
#include "CMenuItem.hpp"

class CMenu {
private:
    std::vector<std::shared_ptr<CMenuItem>> items;
    int nextId = 1;

public:
  void addFoodItem(const std::string &name, double price, bool vegetarian, int calories);
  void addDrinkItem(const std::string &name, double price, bool alcoholic, int volume);
  void addDesertItem(const std::string &name, double price, bool sugarFree, int calories);

  std::shared_ptr<CMenuItem> findById(int id);
  bool removeItem(int id);

  void sortAndReassignIds();
  void saveToFile(const std::string &filename) const;
  void loadFromFile(const std::string &filename);

  void displayMenu() const;
  const std::vector<std::shared_ptr<CMenuItem>> &getItems() const;
};
