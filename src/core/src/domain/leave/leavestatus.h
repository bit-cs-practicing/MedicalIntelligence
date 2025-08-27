#ifndef LEAVESTATUS_H
#define LEAVESTATUS_H

#include <QString>

class LeaveStatus {
public:
    static const QString ACTIVE;
    static const QString CANCELED;

    LeaveStatus(const QString& status);

    QString getValue() const;

private:
    QString status;
};

#endif // LEAVESTATUS_H
