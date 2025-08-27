#ifndef LEAVEPERIOD_H
#define LEAVEPERIOD_H

#include <QDateTime>

class LeavePeriod {
public:
    LeavePeriod(const QDateTime& startTime, const QDateTime& endTime);

    const QDateTime& getStartTime() const;
    const QDateTime& getEndTime() const;

private:
    QDateTime startTime;
    QDateTime endTime;
};

#endif // LEAVEPERIOD_H
