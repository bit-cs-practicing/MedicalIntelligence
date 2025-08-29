#ifndef ATTENDANCEREPOSITORY_H
#define ATTENDANCEREPOSITORY_H

#include "attendance.h"
#include <optional>
#include <QList>

class AttendanceRepository {
public:
    virtual ~AttendanceRepository() = default;

    virtual void save(const Attendance& attendance) = 0;
    virtual std::optional<Attendance> getById(const Id& attendanceId) const = 0;
    virtual std::optional<Attendance> getLastByDoctorIdOrderedByTime(const Id& doctorId) const = 0;
    virtual QList<Attendance> getAllByDoctorId(const Id& doctorId) const = 0;
};

#endif // ATTENDANCEREPOSITORY_H
