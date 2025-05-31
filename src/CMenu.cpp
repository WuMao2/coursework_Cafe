#include "CMenu.hpp"
#include "CFoodItem.hpp"
#include "CDrinkItem.hpp"
#include "CDesertItem.hpp"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

void CMenu::addFoodItem(const std::string &name, double price, bool vegetarian, int calories) {
  items.push_back(std::make_shared<CFoodItem>(nextId++, name, price, vegetarian, calories));
  this->sortAndReassignIds(); // Ensure items are sorted and IDs reassigned after adding
}

void CMenu::addDrinkItem(const std::string &name, double price, bool alcoholic, int volume) {
  items.push_back(std::make_shared<CDrinkItem>(nextId++, name, price, alcoholic, volume));
  this->sortAndReassignIds(); // Ensure items are sorted and IDs reassigned after adding
}

void CMenu::addDesertItem(const std::string &name, double price, bool sugarFree, int calories) {
  items.push_back(std::make_shared<CDesertItem>(nextId++, name, price, sugarFree, calories));
  this->sortAndReassignIds(); // Ensure items are sorted and IDs reassigned after adding
}
      
void CMenu::displayMenu() const {
  for (const auto &item : items) {
      item->display();
  }
}

std::shared_ptr<CMenuItem> CMenu::findById(int id) {
  for (const auto &item : items) {
    if (item->getId() == id)
      return item;
  }
  return nullptr;
}

bool CMenu::removeItem(int id) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if ((*it)->getId() == id) {
      items.erase(it);
      return true;
    }
  }
  return false;
}

void CMenu::sortAndReassignIds() {

    std::vector<std::shared_ptr<CMenuItem>> foodItems;
    std::vector<std::shared_ptr<CMenuItem>> drinkItems;
    std::vector<std::shared_ptr<CMenuItem>> desertItems;

    for (auto& item : items) {
        if (std::dynamic_pointer_cast<CFoodItem>(item))
            foodItems.push_back(item);
        else if (std::dynamic_pointer_cast<CDrinkItem>(item))
            drinkItems.push_back(item);
        else if (std::dynamic_pointer_cast<CDesertItem>(item))
            desertItems.push_back(item);
    }


    items.clear();
    items.insert(items.end(), foodItems.begin(), foodItems.end());
    items.insert(items.end(), drinkItems.begin(), drinkItems.end());
    items.insert(items.end(), desertItems.begin(), desertItems.end());


    int newId = 1;
    for (auto& item : items) {
        item->setId(newId++);
    }


    nextId = newId;
}


void CMenu::saveToFile(const std::string &filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open menu file for writing.\n";
    return;
  }

  for (const auto &item : items) {
    file << item->serialize() << '\n';
  }

  file.close();
}

void CMenu::loadFromFile(const std::string& filename) {
  items.clear();
  nextId = 1; // Reset on load, will re-calculate below

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open menu file for reading.\n";
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string type;
    ss >> type;

    if (type == "Food") {
      int id, calories, vegetarian;
      std::string name;
      double price;

      ss >> id >> name >> price;
      ss.ignore(); // Skip space or quote
      ss >> vegetarian >> calories;

      items.push_back(std::make_shared<CFoodItem>(id, name, price, vegetarian, calories));
      if (id >= nextId) nextId = id + 1;  // update nextId to be safe
    }
    else if (type == "Drink") {
      int id, volume;
      bool alcoholic;
      std::string name;
      double price;

      ss >> id >> name >> price;
      ss.ignore(); // Skip space or quote
      ss >> std::boolalpha >> alcoholic >> volume;

      items.push_back(std::make_shared<CDrinkItem>(id, name, price, alcoholic, volume));
      if (id >= nextId) nextId = id + 1;  // update nextId to be safe
    }
    else if (type == "Desert") {
      int id, calories;
      bool sugarFree;
      std::string name;
      double price;

      ss >> id >> name >> price;
      ss.ignore(); // Skip space or quote
      ss >> std::boolalpha >> sugarFree >> calories;

      items.push_back(std::make_shared<CDesertItem>(id, name, price, sugarFree, calories));
      if (id >= nextId) nextId = id + 1;  // update nextId to be safe
    }
    // Add other types here as needed
  }

  file.close();
  this->sortAndReassignIds(); // Sort and reassign IDs after loading
  std::cout << "Menu loaded successfully from " << filename << ".\n";
}

const std::vector<std::shared_ptr<CMenuItem>>& CMenu::getItems() const {
  return items;
}