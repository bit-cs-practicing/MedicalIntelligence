#include "attendance.h"

Attendance::Attendance(Id attendanceId, Id doctorId, const QDateTime& attendanceTime)
    : attendanceId(attendanceId), doctorId((doctorId)), attendanceTime(attendanceTime) {}

const Id& Attendance::getAttendanceId() const {
    return attendanceId;
}

const Id &Attendance::getDoctorId() const {
    return doctorId;
}

const QDateTime& Attendance::getAttendanceTime() const {
    return attendanceTime;
}
