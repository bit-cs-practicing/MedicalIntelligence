#ifndef PHONE_H
#define PHONE_H

#include <QString>

class Phone {
public:
    explicit Phone(QString phone);

    const QString& getValue() const;
private:
    QString phone;
};

#endif // PHONE_H
