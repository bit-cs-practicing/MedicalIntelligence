#include "idcard.h"

#include <stdexcept>

IdCard::IdCard(QString id): id(id) {
    for (auto ch : id) {
        if (!ch.isDigit()) {
            throw std::logic_error("身份证号必须由数字组成");
        }
    }
    if (id.length() != 18) {
        throw std::logic_error("身份证号必须有 18 位");
    }
}

const QString& IdCard::getValue() const {
    return this->id;
}
