#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include "../id.h"

#include <QDateTime>

class Attendance {
public:
    Attendance(Id attendanceId, const QDateTime& attendanceTime);

    const Id& getAttendanceId() const;
    const QDateTime& getAttendanceTime() const;

private:
    Id attendanceId;
    QDateTime attendanceTime;
};

#endif // ATTENDANCE_H
