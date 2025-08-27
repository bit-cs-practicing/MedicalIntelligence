#ifndef EMAIL_H
#define EMAIL_H

#include <QString>

class Email {
public:
    explicit Email(QString email);

    const QString& getValue() const;
private:
    QString email;

    void validateEmail(const QString &email);
};

#endif // EMAIL_H
