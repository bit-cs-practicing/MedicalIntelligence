#ifndef NAME_H
#define NAME_H

#include <QString>

class Name {
public:
    explicit Name(QString value);

    const QString& getValue() const;

private:
    QString value;
};

#endif // NAME_H
