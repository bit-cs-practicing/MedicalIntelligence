#include "consultationquestion.h"

#include <stdexcept>

ConsultationQuestion::ConsultationQuestion(QString value): value(value) {
    if (value.isEmpty()) {
        throw std::invalid_argument("问题不可以为空");
    }
}

const QString& ConsultationQuestion::getValue() const {
    return value;
}
