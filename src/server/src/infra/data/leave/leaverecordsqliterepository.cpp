#include "leaverecordsqliterepository.h"

#include "infra/data/util/databaseoperator/databaseoperator.h"

LeaveRecordSQLiteRepository::LeaveRecordSQLiteRepository(const QString& path) {
    DatabaseOperator::createConnection(&db, "LeaveRecord", path);
}

LeaveRecordSQLiteRepository::~LeaveRecordSQLiteRepository() {
    db.close();
}

void LeaveRecordSQLiteRepository::save(const LeaveRecord& leaveRecord) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM leaveRecord WHERE leaveId = :leaveId;");
    query.bindValue(":leaveId", leaveRecord.getLeaveId().getId());
    bool result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";

    query.prepare(
        "INSERT INTO leaveRecord(leaveId,doctorId,startTime,endTime,status) "
        "VALUES (:leaveId,:doctorId,:startTime,:endTime,:status);"
    );
    query.bindValue(":leaveId", leaveRecord.getLeaveId().getId());
    query.bindValue(":doctorId", leaveRecord.getDoctorId().getId());
    query.bindValue(":startTime", leaveRecord.getLeavePeriod().getStartTime().toString(Qt::ISODate));
    query.bindValue(":endTime", leaveRecord.getLeavePeriod().getEndTime().toString(Qt::ISODate));
    query.bindValue(":status", leaveRecord.getLeaveStatus().getValue());
    result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
}

std::optional<LeaveRecord> LeaveRecordSQLiteRepository::getById(const Id& leaveId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM leaveRecord WHERE leaveId = :leaveId;");
    query.bindValue(":leaveId", leaveId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getLeaveRecordFromQuery(query);
}

std::optional<LeaveRecord> LeaveRecordSQLiteRepository::getLastByDoctorId(const Id& doctorId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM leaveRecord WHERE doctorId = :doctorId AND status = 'active';");
    query.bindValue(":doctorId", doctorId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getLeaveRecordFromQuery(query);
}
