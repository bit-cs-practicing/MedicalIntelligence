#include "util.h"

#include <regex>

bool Util::checkName(const QString& name) {
    return name.length() >= 2 && name.length() <= 10;
}

bool Util::checkIdCard(const QString& idCard) {
    int len = idCard.length();
    if (len != 18) return false;
    for (int i = 0; i < len; ++i) {
        if(!idCard[i].isDigit() && (i != len - 1 || idCard[i] != 'X')) {
            return false;
        }
    }
    return true;
}

bool Util::checkPassword(const QString& password) {
    int len = password.length();
    if (len < 7 || len > 20) return false;
    for (int i = 0; i < len; ++i) {
        if (!password[i].isDigit() && !password[i].isLower() && !password[i].isUpper()) {
            return false;
        }
    }
    return true;
}

bool Util::checkEmail(const std::string& email) {
    static const std::regex emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, emailRegex);
}

bool Util::checkPhone(const QString& phone) {
    if (phone.length() != 11 || phone[0] != '1') {
        return false;
    }
    for (int i = 1; i < 11; ++i) {
        if(!phone[i].isDigit()) {
            return false;
        }
    }
    return true;
}

QString Util::transferGenderFromZHToEN(const QString& ZHContext) {
    if (ZHContext == QString("男")) {
        return "male";
    } else {
        return "female";
    }
}
