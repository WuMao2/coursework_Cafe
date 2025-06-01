#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

class CMenuItem {
  protected:
    std::string name;
    double price;
    int id;

  public:
    CMenuItem(int id, const std::string& name, double price)
          : id(id), name(name), price(price) {}

    virtual ~CMenuItem() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }

    void setName(const std::string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setId(int newId) { id = newId; }

    virtual std::string getType() const = 0;
    virtual std::string serialize() const = 0;
    virtual void display() const = 0;

};