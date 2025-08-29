#ifndef ATTENDANCEFACTORY_H
#define ATTENDANCEFACTORY_H

#include <memory>
#include <QTime>

#include "../doctor/doctor.h"
#include "attendancerepository.h"

class AttendanceFactory {
public:
    AttendanceFactory(std::shared_ptr<AttendanceRepository> attendanceRepository);

    Attendance createAttendance(const Doctor& doctor) const;
private:
    std::shared_ptr<AttendanceRepository> attendanceRepository;

    void checkTimeInSchedule(const QTime& currentTime, const Doctor& doctor) const;
    void checkNoAttendanceToday(const QDate& currentDate, const Doctor& doctor) const;
};

#endif // ATTENDANCEFACTORY_H
