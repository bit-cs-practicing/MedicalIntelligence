#include "phone.h"

#include <stdexcept>

Phone::Phone(QString phone): phone(phone) {
    for (auto ch : this->phone) {
        if (!ch.isDigit()) {
            throw std::logic_error("电话号码必须由数字组成");
        }
    }
    if (this->phone.length() != 11) {
        throw std::logic_error("电话号码必须有 11 位");
    }
}

const QString& Phone::getValue() const {
    return this->phone;
}
