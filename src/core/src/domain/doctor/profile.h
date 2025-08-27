#ifndef PROFILE_H
#define PROFILE_H

#include <QString>

class Profile {
public:
    explicit Profile(QString profile);

    const QString& getValue() const;
private:
    QString profile;
};

#endif // PROFILE_H
