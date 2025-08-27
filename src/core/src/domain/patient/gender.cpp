#include "gender.h"

#include <stdexcept>

Gender::Gender(QString gender): gender(gender.toLower()) {
    if (this->gender != "male" && this->gender != "female") {
        throw std::logic_error("性别必须为男 (male) 或女 (female)");
    }
}

const QString& Gender::getValue() const {
    return this->gender;
}
