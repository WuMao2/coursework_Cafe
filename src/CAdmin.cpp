#include "CAdmin.hpp"
#include <string>

CAdmin::CAdmin(const std::string& u, const std::string& p, bool s, long int id)
    : username(u), password(p), employeeId(id) {}

long int CAdmin::getEmployeeId() const {
    return employeeId;
}

std::string CAdmin::getUsername() const {
    return username;
}
