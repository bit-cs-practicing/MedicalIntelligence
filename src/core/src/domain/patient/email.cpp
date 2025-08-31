#include "email.h"

#include <stdexcept>

#include <QRegularExpression>

Email::Email(QString email) : email(email) {
    validateEmail(email);
}

const QString& Email::getValue() const {
    return email;
}

void Email::validateEmail(const QString& email) {
    if (email.isEmpty()) {
        throw std::invalid_argument("电子邮箱不可以为空");
    }
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9_+&*-]+(?:\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,7}$)");
    QRegularExpressionMatch match = emailRegex.match(email);
    if (!match.hasMatch()) {
        throw std::invalid_argument("无效的电子邮箱格式");
    }
}
