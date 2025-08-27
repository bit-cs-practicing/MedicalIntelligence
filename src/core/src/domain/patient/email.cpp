#include "email.h"

#include <stdexcept>

Email::Email(QString email): email(email) {
    if (this->email.isEmpty()) {
        throw std::logic_error("电子邮箱不可以为空");
    }
}
