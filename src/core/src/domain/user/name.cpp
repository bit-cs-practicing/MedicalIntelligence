#include "name.h"

#include <stdexcept>

Name::Name(QString value): value(value) {
    if (this->value.isEmpty()) {
        throw std::logic_error("名字不可以为空");
    }
}

const QString& Name::getValue() const {
    return this->value;
}
