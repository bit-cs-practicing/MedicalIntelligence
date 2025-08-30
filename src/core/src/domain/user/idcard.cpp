#include "idcard.h"

#include <stdexcept>

IdCard::IdCard(QString id): id(id) {
    if (id.length() != 18) {
        throw std::logic_error("身份证号必须有 18 位");
    }
    for (int i = 0; i <= 16; i++) {
        if (!id[i].isDigit()) {
            throw std::logic_error("身份证号前17位必须由数字组成");
        }
    }
    if (!id[17].isDigit() && id[17] != 'X')
        throw std::logic_error("身份证号第18位必须由数字或X组成");
}

const QString& IdCard::getValue() const {
    return this->id;
}
