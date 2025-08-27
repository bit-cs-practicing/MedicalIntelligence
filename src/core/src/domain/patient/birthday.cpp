#include "birthday.h"

Birthday::Birthday(QDate birthday): birthday(birthday) {

}

const QDate& Birthday::getValue() const {
    return this->birthday;
}
