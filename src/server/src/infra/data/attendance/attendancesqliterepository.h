#ifndef ATTENDANCESQLITEREPOSITORY_H
#define ATTENDANCESQLITEREPOSITORY_H

#include <QtSql/QSqlDatabase>
#include <QString>
#include <optional>

#include "core/src/domain/attendance/attendancerepository.h"

class AttendanceSQLiteRepository : public AttendanceRepository
{
public:
    AttendanceSQLiteRepository(const QString& path);
    ~AttendanceSQLiteRepository();
    void save(const Attendance& attendance) override;
    std::optional<Attendance> getById(const Id &attendanceId) const override;
    std::optional<Attendance> getLastByDoctorIdOrderedByTime(const Id &doctorId) const override;
    QList<Attendance> getAllByDoctorId(const Id &doctorId) const override;
private:
    QSqlDatabase db;
};

#endif // ATTENDANCESQLITEREPOSITORY_H
