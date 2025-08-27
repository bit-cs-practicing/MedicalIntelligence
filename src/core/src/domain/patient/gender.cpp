#include "gender.h"

#include <stdexcept>

const QString MALE = "male";
const QString FEMALE = "female";

Gender::Gender(QString gender): gender(gender.toLower()) {
    if (this->gender != Gender::MALE && this->gender != Gender::FEMALE) {
        throw std::invalid_argument("性别必须为男 (male) 或女 (female)");
    }
}

const QString& Gender::getValue() const {
    return this->gender;
}
