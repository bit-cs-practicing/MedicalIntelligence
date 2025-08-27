#ifndef APPOINTMENTTIMESLOT_H
#define APPOINTMENTTIMESLOT_H

#include <QTime>

class AppointmentTimeSlot {
public:
    AppointmentTimeSlot(const QTime& startTime, const QTime& endTime);

    const QTime& getStartTime() const;
    const QTime& getEndTime() const;
    QString toString() const;
    static AppointmentTimeSlot parse(const QString& timeSlotStr);
private:
    QTime startTime;
    QTime endTime;
};

#endif // APPOINTMENTTIMESLOT_H
