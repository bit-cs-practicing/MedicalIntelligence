#include "consultationanswer.h"

#include <stdexcept>

ConsultationAnswer::ConsultationAnswer(QString value): value(value) {
    if (value.isEmpty()) {
        throw std::invalid_argument("回答不可以为空");
    }
}

const QString& ConsultationAnswer::getValue() const {
    return value;
}
