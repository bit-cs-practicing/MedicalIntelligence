#ifndef ID_H
#define ID_H

#include <QString>

class Id {
public:
    Id(QString id);

    static Id fromUuid();

    const QString& getId() const;

private:
    QString id;
};

#endif // ID_H
