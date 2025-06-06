#pragma once
#include <vector>
#include <string>
#include "COrder.hpp"
#include "CAdmin.hpp"

class COrderList {
private:
    std::vector<COrder> orders;
public:
  void addOrder(const COrder &order);
  void removeOrder(const int tableId);
  bool markOrderAsFinished(int id);
  bool removeOrder(CAdmin* admin, int id);

  void loadFromFile(const std::string &filename);
  void saveToFile(const std::string &filename) const;
  
  const std::vector<COrder> &getOrders() const;

  void printAllOrders() const;
  void fixOrderIds();
};
