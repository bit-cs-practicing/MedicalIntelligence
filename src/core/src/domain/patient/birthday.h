#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <QDate>

class Birthday {
public:
    explicit Birthday(QDate birthday);

    static Birthday parse(const QString& str);

    const QDate& getValue() const;
    QString toString() const;
private:
    QDate birthday;
};

#endif // BIRTHDAY_H
