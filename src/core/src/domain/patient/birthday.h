#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <QDate>

class Birthday {
public:
    explicit Birthday(QDate birthday);

    const QDate& getValue() const;
private:
    QDate birthday;
};

#endif // BIRTHDAY_H
