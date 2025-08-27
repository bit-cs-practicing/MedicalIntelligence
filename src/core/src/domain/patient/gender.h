#ifndef GENDER_H
#define GENDER_H

#include <QString>

class Gender {
public:
    static const QString MALE;
    static const QString FEMALE;

    explicit Gender(QString gender);

    const QString& getValue() const;
private:
    QString gender;
};

#endif // GENDER_H
