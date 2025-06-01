#include "CAdmin.hpp"
#include <string>

CAdmin::CAdmin(const std::string& u, const std::string& p, bool s, long int id)
    : CUser(u, p, s), employeeId(id) {}

long int CAdmin::getEmployeeId() const {
    return employeeId;
}
