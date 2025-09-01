#include "attendancesqliterepository.h"

#include <QDebug>
#include <QVariant>

#include "infra/data/util/databaseoperator/databaseoperator.h"

AttendanceSQLiteRepository::AttendanceSQLiteRepository(const QUrl& path) {
    DatabaseOperator::createConnection(&db, "Attendance", path);
}

AttendanceSQLiteRepository::~AttendanceSQLiteRepository() {
    db.close();
}

void AttendanceSQLiteRepository::save(const Attendance &attendance) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM attendance WHERE attendanceId = :attendanceId;");
    query.bindValue(":attendanceId", attendance.getAttendanceId().getId());
    bool result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";

    query.prepare(
        "INSERT INTO attendance(attendanceId,doctorId,attendanceTime) "
        "VALUES (:attendanceId,:doctorId,:attendanceTime);"
    );
    query.bindValue(":attendanceId", attendance.getAttendanceId().getId());
    query.bindValue(":doctorId", attendance.getDoctorId().getId());
    query.bindValue(":attendanceTime", attendance.getAttendanceTime().toString(Qt::ISODate));

    result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
}

std::optional<Attendance> AttendanceSQLiteRepository::getById(const Id &attendanceId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM attendance WHERE attendanceId = :attendanceId;");
    query.bindValue(":attendanceId", attendanceId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getAttendanceFromQuery(query);
}

std::optional<Attendance> AttendanceSQLiteRepository::getLastByDoctorIdOrderedByTime(const Id &doctorId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM attendance "
                  "WHERE doctorId = :doctorId "
                  "ORDER BY attendanceTime DESC;");
    query.bindValue(":doctorId", doctorId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getAttendanceFromQuery(query);
}

QList<Attendance> AttendanceSQLiteRepository::getAllByDoctorId(const Id &doctorId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM attendance WHERE doctorId = :doctorId;");
    query.bindValue(":doctorId", doctorId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Attendance> que;
    while(query.next())
        que.push_back(DatabaseOperator::getAttendanceFromQuery(query));
    return que;
}
