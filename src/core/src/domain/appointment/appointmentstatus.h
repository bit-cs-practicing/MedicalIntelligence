#ifndef APPOINTMENTSTATUS_H
#define APPOINTMENTSTATUS_H

#include <QString>

class AppointmentStatus {
public:
    static const QString SCHEDULED;
    static const QString COMPLETED;
    static const QString CANCELLED;

    explicit AppointmentStatus(const QString& status);

    const QString& getValue() const;

private:
    QString status;
};

#endif // APPOINTMENTSTATUS_H
