#ifndef GENDER_H
#define GENDER_H

#include <QString>

class Gender {
public:
    explicit Gender(QString gender);

    const QString& getValue() const;
private:
    QString gender;
};

#endif // GENDER_H
