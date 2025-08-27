#include "password.h"

#include <stdexcept>

Password::Password(QString password): password(password) {
    if (this->password.isEmpty()) {
        throw std::logic_error("密码不可以为空");
    }
}

const QString& Password::getValue() const {
    return this->password;
}
