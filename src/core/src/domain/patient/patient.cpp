#include "patient.h"

Patient::Patient(Name name, IdCard idCard, Gender gender, Phone phone, Password password)
    : User(name, idCard, password)
    , gender(gender)
    , phone(phone)
    , birthday(std::nullopt)
    , email(std::nullopt)
    , emergencyContact(std::nullopt)
{
}

const Gender& Patient::getGender() const {
    return gender;
}

void Patient::setGender(Gender value) {
    gender = value;
}

const Phone& Patient::getPhone() const {
    return phone;
}

void Patient::setPhone(Phone value) {
    phone = value;
}

const std::optional<Birthday>& Patient::getBirthday() const {
    return birthday;
}

void Patient::setBirthday(Birthday value) {
    birthday = std::make_optional(value);
}

const std::optional<Email>& Patient::getEmail() const {
    return email;
}

void Patient::setEmail(Email value) {
    email = std::make_optional(value);
}

const std::optional<Phone>& Patient::getEmergencyContact() const {
    return emergencyContact;
}

void Patient::setEmergencyContact(Phone value) {
    emergencyContact = std::make_optional(value);
}
