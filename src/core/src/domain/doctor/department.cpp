#include "department.h"

#include <stdexcept>

Department::Department(QString department): department(department) {
    if (this->department.isEmpty()) {
        throw std::logic_error("科室不可以为空");
    }
}

const QString& Department::getValue() const {
    return this->department;
}
