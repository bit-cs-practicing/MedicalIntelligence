#include "employeeid.h"

#include <stdexcept>

EmployeeId::EmployeeId(QString employeeId): employeeId(employeeId) {
    if (employeeId.isEmpty()) {
        throw std::invalid_argument("工号不可以为空");
    }
}

const QString& EmployeeId::getValue() const {
    return this->employeeId;
}
