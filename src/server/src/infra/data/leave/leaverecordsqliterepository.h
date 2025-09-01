#ifndef LEAVERECORDSQLITEREPOSITORY_H
#define LEAVERECORDSQLITEREPOSITORY_H

#include "domain/leave/leaverecordrepository.h"

#include <QtSql>

class LeaveRecordSQLiteRepository : public LeaveRecordRepository
{
public:
    LeaveRecordSQLiteRepository(const QUrl& path);
    ~LeaveRecordSQLiteRepository();
    void save(const LeaveRecord& leaveRecord) override;
    std::optional<LeaveRecord> getById(const Id& leaveId) const override;
    std::optional<LeaveRecord> getLastByDoctorId(const Id& doctorId) const override;
private:
    QSqlDatabase db;
};

#endif // LEAVERECORDSQLITEREPOSITORY_H
