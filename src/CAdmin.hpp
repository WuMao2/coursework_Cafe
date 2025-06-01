#pragma once
#include "CUser.hpp"

class CAdmin : public CUser {
private:
    long int employeeId;

public:
    CAdmin(const std::string& username, const std::string& password, bool status, long int id);
    virtual ~CAdmin() = default;

    // Optional getter for employee ID if needed later
    long int getEmployeeId() const;
};

