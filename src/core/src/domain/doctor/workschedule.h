#ifndef WORKSCHEDULE_H
#define WORKSCHEDULE_H

#include <QString>

class WorkSchedule {
public:
    explicit WorkSchedule(QString workSchedule);

    const QString& getValue() const;

private:
    QString workSchedule;
};

#endif // WORKSCHEDULE_H
