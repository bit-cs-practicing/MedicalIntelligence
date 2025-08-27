#ifndef APPOINTMENTSTATUS_H
#define APPOINTMENTSTATUS_H

#include <QString>

class AppointmentStatus {
public:
    explicit AppointmentStatus(const QString& status);

    const QString& getValue() const;

private:
    QString status;
};

#endif // APPOINTMENTSTATUS_H
