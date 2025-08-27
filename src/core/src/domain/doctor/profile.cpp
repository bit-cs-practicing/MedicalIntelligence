#include "profile.h"

#include <stdexcept>

Profile::Profile(QString profile): profile(profile) {
    if (profile.isEmpty()) {
        throw std::invalid_argument("个人资料不能为空");
    }
    if (profile.length() > 200) {
        throw std::invalid_argument("个人资料不能超过 200 个字符");
    }
}

const QString& Profile::getValue() const {
    return this->profile;
}
