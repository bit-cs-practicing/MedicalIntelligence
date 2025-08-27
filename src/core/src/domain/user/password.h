#ifndef PASSWORD_H
#define PASSWORD_H

#include <QString>

class Password {
public:
    explicit Password(QString password);

    const QString& getValue() const;
private:
    QString password;
};

#endif // PASSWORD_H
