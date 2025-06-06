#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "Utils.hpp"

void awaitForInput() {
    std::cout << "\nPress Enter to continue...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int strictInput() {
    std::string input;
    int choice;

    // Clear previous errors (if any)
    std::cin.clear();

    std::getline(std::cin, input);

    std::stringstream ss(input);
    if (ss >> choice && ss.eof()) {
        return choice;
    } else {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        awaitForInput();
        return -1;
    }
}

double strictInputDouble() {
    std::string input;
    double value;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    if (ss >> value && ss.eof()) {
        return value;
    } else {
        std::cout << "Invalid input. Please enter a valid number." << std::endl;
        awaitForInput();
        return -1;
    }
}

bool strictInputBool() {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        return false; // Default to false if no input
    }

    char firstChar = input[0];
    if (firstChar == 'y' || firstChar == 'Y') {
        return true;
    } else if (firstChar == 'n' || firstChar == 'N') {
        return false;
    } else {
        std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        return strictInputBool(); // Retry
    }
}

void logToFile(const std::string& message) {
    std::ofstream logFile("session_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
}