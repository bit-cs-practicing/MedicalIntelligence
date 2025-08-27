#include "employeeid.h"

#include <stdexcept>

EmployeeId::EmployeeId(QString employeeId): employeeId(employeeId) {
    if (employeeId.isEmpty()) {
        throw std::logic_error("工号不可以为空");
    }
}

const QString& EmployeeId::getValue() const {
    return this->employeeId;
}
