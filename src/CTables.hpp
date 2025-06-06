#include <vector>
#include <string>
#include "CAdmin.hpp"
#pragma once

class CTables {
public:
    // Constructor
    CTables() = default;

    // Destructor
    ~CTables() = default;

    void loadTablesFromFile(const std::string &filename);
    void saveTablesToFile(const std::string &filename) const;
    void displayTables() const;
    void displayTables(CAdmin* admin) const;
    void occupyTable(int tableId);
    void freeTable(int tableId);
    bool isTableOccupied(int tableId) const;

private:
    std::vector<int> occupiedTables; // Vector to store occupied table IDs
    std::vector<int> freeTables;      // Vector to store free table IDs
    int maxTableId = 0; // Maximum table ID, can be used for validation or future expansion
};