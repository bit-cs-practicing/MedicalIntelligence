#ifndef ATTENDANCESQLITEREPOSITORY_H
#define ATTENDANCESQLITEREPOSITORY_H

#include "domain/attendance/attendancerepository.h"

#include <QtSql>

class AttendanceSQLiteRepository : public AttendanceRepository {
public:
    AttendanceSQLiteRepository(const QUrl& path);
    ~AttendanceSQLiteRepository();
    void save(const Attendance& attendance) override;
    std::optional<Attendance> getById(const Id &attendanceId) const override;
    std::optional<Attendance> getLastByDoctorIdOrderedByTime(const Id &doctorId) const override;
    QList<Attendance> getAllByDoctorId(const Id &doctorId) const override;
private:
    QSqlDatabase db;
};

#endif // ATTENDANCESQLITEREPOSITORY_H
