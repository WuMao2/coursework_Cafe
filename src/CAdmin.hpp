#pragma once
#include <iostream>
#include <string>

class CAdmin {
private:
    std::string username;
    std::string password;
    long int employeeId;

public:
    CAdmin(const std::string& username, const std::string& password, bool status, long int id);
    virtual ~CAdmin() = default;

    // Optional getter for employee ID if needed later
    long int getEmployeeId() const;
    std::string getUsername() const;
};

