#include "appointmentsqliterepository.h"

#include <QDebug>

#include "infra/data/util/databaseoperator/databaseoperator.h"

AppointmentSQLiteRepository::AppointmentSQLiteRepository(const QString& path) {
    DatabaseOperator::createConnection(&db, "Appointment", path);
}

AppointmentSQLiteRepository::~AppointmentSQLiteRepository() {db.close();}

void AppointmentSQLiteRepository::save(const Appointment &appointment) {
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO appointment(appointmentId,doctorId,patientId,"
        "date,startTime,endTime,status) "
        "VALUES (:appointmentId,:doctorId,:patientId,"
        ":date,:startTime,:endTime,:status);"
    );
    query.bindValue(":appointmentId", appointment.getAppointmentId().getId());
    query.bindValue(":doctorId", appointment.getDoctorId().getId());
    query.bindValue(":patientId", appointment.getPatientId().getId());
    query.bindValue(":date", appointment.getDate().toString(Qt::ISODate));
    static const QString format("hh:mm:ss");
    query.bindValue(":startTime", appointment.getTimeSlot().getStartTime().toString(format));
    query.bindValue(":endTime", appointment.getTimeSlot().getEndTime().toString(format));
    query.bindValue(":status", appointment.getStatus().getValue());
    bool result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
}

std::optional<Appointment> AppointmentSQLiteRepository::getById(const Id &appointmentId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM appointment WHERE appointmentId = :appointmentId;");
    query.bindValue(":appointmentId", appointmentId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getAppointmentFromQuery(query);
}

QList<Appointment> AppointmentSQLiteRepository::getAllByPatientId(const Id& patientId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM appointment WHERE patientId = :patientId;");
    query.bindValue(":patientId", patientId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Appointment> que;
    while(query.next())
        que.push_back(DatabaseOperator::getAppointmentFromQuery(query));
    return que;
}

QList<Appointment> AppointmentSQLiteRepository::getAllByDoctorId(const Id& doctorId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM appointment WHERE doctorId = :doctorId;");
    query.bindValue(":doctorId", doctorId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Appointment> que;
    while(query.next())
        que.push_back(DatabaseOperator::getAppointmentFromQuery(query));
    return que;
}

QList<Appointment> AppointmentSQLiteRepository::getAllByDoctorIdAndPatientId(const Id& doctorId, const Id& patientId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM appointment WHERE doctorId = :doctorId AND patientId = :patientId;");
    query.bindValue(":doctorId", doctorId.getId());
    query.bindValue(":patientId", patientId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Appointment> que;
    while(query.next())
        que.push_back(DatabaseOperator::getAppointmentFromQuery(query));
    return que;
}

QList<Appointment> AppointmentSQLiteRepository::getAllByDoctorIdAndDate(const Id& doctorId, const QDate& date) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM appointment WHERE doctorId = :doctorId AND date = :date;");
    query.bindValue(":doctorId", doctorId.getId());
    query.bindValue(":date", date.toString(Qt::ISODate));
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Appointment> que;
    while(query.next())
        que.push_back(DatabaseOperator::getAppointmentFromQuery(query));
    return que;
}
