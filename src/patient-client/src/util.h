#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <string>

class Util
{
public:
    static bool checkName(const QString& name);
    static bool checkIdCard(const QString& idCard);
    static bool checkPassword(const QString& password);
    static bool checkEmail(const std::string& email);
    static bool checkPhone(const QString& phone);
    static QString transferGenderFromZHToEN(const QString& ZHContext);
};

#endif // UTIL_H
