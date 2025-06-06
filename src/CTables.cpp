#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CTables.hpp"

void CTables::loadTablesFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open " << filename << " for reading.\n";
        return;
    }
    occupiedTables.clear();
    freeTables.clear();
    int tableId;
    while (file >> tableId) {
      //sorting tabes while remembering the highest table ID
        if (abs(tableId) > maxTableId) {
            maxTableId = abs(tableId);
        }
        if (tableId < 0) {
            occupiedTables.push_back(-tableId); // Store as positive for occupied tables
        } else {
            freeTables.push_back(tableId);
        }
    }
    file.close();
}

void CTables::saveTablesToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open " << filename << " for writing.\n";
        return;
    }
    for (const auto &tableId : occupiedTables) {
        file << -tableId << "\n"; // Store as negative for occupied tables
    }
    for (const auto &tableId : freeTables) {
        file << tableId << "\n"; // Store as positive for free tables
    }
    file.close();
}

void CTables::displayTables() const {
    std::cout << "\nFree Tables: ";
    for (const auto &tableId : freeTables) {
        std::cout << tableId << " ";
    }
    std::cout << std::endl;
}

void CTables::displayTables(CAdmin* admin) const {
    if (admin) {
        std::cout << "\nOccupied Tables: ";
        for (const auto &tableId : occupiedTables) {
            std::cout << tableId << " ";
        }
        std::cout << std::endl;
        displayTables();
    } else {
        displayTables();
    }
}

void CTables::occupyTable(int tableId) {
    auto it = std::find(freeTables.begin(), freeTables.end(), tableId);
    if (it != freeTables.end()) {
        freeTables.erase(it);
        occupiedTables.push_back(tableId);
    } else {
        std::cout << "Table " << tableId << " is not available.\n";
    }
}

void CTables::freeTable(int tableId) {
    //check if table ID is higher than maxTableId
    if (tableId > maxTableId) {
        std::cout << "Invalid table ID: " << tableId << ". It exceeds the maximum table ID.\n";
        return;
    }
    auto it = std::find(occupiedTables.begin(), occupiedTables.end(), tableId);
    if (it != occupiedTables.end()) {
        occupiedTables.erase(it);
        freeTables.push_back(tableId);
        std::cout << "Table ID " << tableId << " is now free.\n";
    } else {
        std::cout << "Table " << tableId << " is not occupied.\n";
    }
}

bool CTables::isTableOccupied(int tableId) const {
    //check if table ID is higher than maxTableId
    if (tableId > maxTableId) {
        return true;
    }
    return std::find(occupiedTables.begin(), occupiedTables.end(), tableId) != occupiedTables.end();
}
