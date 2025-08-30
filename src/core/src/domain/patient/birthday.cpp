#include "birthday.h"

#include <exception>

Birthday::Birthday(QDate birthday): birthday(birthday) {

}

Birthday Birthday::parse(const QString &str) {
    try {
        auto birthday = QDate::fromString(str, "yyyy-MM-dd");
        return Birthday(birthday);
    } catch (std::exception& e) {
        throw std::invalid_argument("生日格式必须为 yyyy-MM-dd");
    }
}

const QDate& Birthday::getValue() const {
    return this->birthday;
}

QString Birthday::toString() const {
    return birthday.toString("yyyy-MM-dd");
}
