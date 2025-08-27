#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QString>

class Department {
public:
    explicit Department(QString department);

    const QString& getValue() const;
private:
    QString department;
};

#endif // DEPARTMENT_H
