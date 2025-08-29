#ifndef WORKSCHEDULE_H
#define WORKSCHEDULE_H

#include <QString>
#include <QTime>

class WorkSchedule {
public:
    explicit WorkSchedule(QTime startTime, QTime endTime);

    static WorkSchedule fromString(const QString& str);
    QString toString() const;

    QTime getStartTime() const;
    QTime getEndTime() const;

private:
    QTime startTime;
    QTime endTime;
};

#endif // WORKSCHEDULE_H
