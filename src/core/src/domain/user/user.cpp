#include "user.h"

const QString User::ROLE_DOCTOR = "doctor";
const QString User::ROLE_PATIENT = "patient";

User::User(Name name, IdCard idCard, Password password)
    : name(name)
    , idCard(idCard)
    , password(password)
{
}


Name User::getName() const {
    return name;
}

void User::setName(const Name &value) {
    name = value;
}

IdCard User::getIdCard() const {
    return idCard;
}

void User::setIdCard(const IdCard &value) {
    idCard = value;
}

Password User::getPassword() const {
    return password;
}

void User::setPassword(const Password &value) {
    password = value;
}

Id User::getId() const {
    return Id(this->getRole() + this->idCard.getValue());
}
