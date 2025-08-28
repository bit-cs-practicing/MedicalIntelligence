#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include "../id.h"

#include <QDateTime>

class Attendance {
public:
    Attendance(Id attendanceId, Id doctorId, const QDateTime& attendanceTime);

    const Id& getAttendanceId() const;
    const Id& getDoctorId() const;
    const QDateTime& getAttendanceTime() const;

private:
    Id attendanceId;
    Id doctorId;
    QDateTime attendanceTime;
};

#endif // ATTENDANCE_H
