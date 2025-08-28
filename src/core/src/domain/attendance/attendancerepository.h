#ifndef ATTENDANCEREPOSITORY_H
#define ATTENDANCEREPOSITORY_H

#include "attendance.h"
#include <optional>
#include <QList>

class AttendanceRepository {
public:
    virtual ~AttendanceRepository() = 0;

    virtual void save(const Attendance& attendance) = 0;
    virtual std::optional<Attendance> getById(const Id& attendanceId) = 0;
    virtual QList<Attendance> getByDoctorId(const Id& doctorId) = 0;
};

#endif // ATTENDANCEREPOSITORY_H
