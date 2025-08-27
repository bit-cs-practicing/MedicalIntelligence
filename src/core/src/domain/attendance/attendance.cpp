#include "attendance.h"

Attendance::Attendance(Id attendanceId, const QDateTime& attendanceTime)
    : attendanceId(attendanceId), attendanceTime(attendanceTime) {}

const Id& Attendance::getAttendanceId() const {
    return attendanceId;
}

const QDateTime& Attendance::getAttendanceTime() const {
    return attendanceTime;
}
