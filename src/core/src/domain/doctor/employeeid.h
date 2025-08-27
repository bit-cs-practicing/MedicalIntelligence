#ifndef EMPLOYEEID_H
#define EMPLOYEEID_H

#include <QString>

class EmployeeId {
public:
    explicit EmployeeId(QString employeeId);

    const QString& getValue() const;

private:
    QString employeeId;
};

#endif // EMPLOYEEID_H
