#include "doctorsqliterepository.h"

#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QVariant>

#include "infra/data/util/databaseoperator/databaseoperator.h"

DoctorSQLiteRepository::DoctorSQLiteRepository(const QString& path) {
    DatabaseOperator::createConnection(&db, "Doctor", path);
}

DoctorSQLiteRepository::~DoctorSQLiteRepository() {
    db.close();
}

void DoctorSQLiteRepository::save(const Doctor& doctor) {
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO doctor(id,name,idCard,password,employeeId,"
        "department,profile,photo,startTime,endTime,"
        "registrationFee,dailyPatientLimit) "
        "VALUES (:id,:name,:idCard,:password,:employeeId,"
        ":department,:profile,:photo,:startTime,:endTime,"
        ":registrationFee,:dailyPatientLimit);"
    );
    DatabaseOperator::addUserInfo(&query, doctor);
    if (doctor.getEmployeeId().has_value())
        query.bindValue(":employeeId", doctor.getEmployeeId()->getValue());
    else query.bindValue(":employeeId", "");
    if (doctor.getDepartment().has_value())
        query.bindValue(":department", doctor.getDepartment()->getValue());
    else query.bindValue(":department", "");
    if (doctor.getProfile().has_value())
        query.bindValue(":profile", doctor.getProfile()->getValue());
    else query.bindValue(":profile", "");
    if (doctor.getPhoto().has_value())
        query.bindValue(":photo", doctor.getPhoto()->toString());
    else query.bindValue(":photo", "");

    if (doctor.getWorkSchedule().has_value()) {
        static const QString format("hh:mm:ss");
        query.bindValue(":startTime", doctor.getWorkSchedule()->getStartTime().toString(format));
        query.bindValue(":endTime", doctor.getWorkSchedule()->getEndTime().toString(format));
    }
    else {
        query.bindValue(":startTime", "");
        query.bindValue(":endTime", "");
    }

    if (doctor.getRegistrationFee().has_value())
        query.bindValue(":registrationFee", doctor.getRegistrationFee()->getValue());
    else query.bindValue(":registrationFee", "");
    if (doctor.getRegistrationFee().has_value())
        query.bindValue(":dailyPatientLimit", doctor.getDailyPatientLimit()->getValue());
    else query.bindValue(":dailyPatientLimit", "");

    bool result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
}

std::optional<Doctor> DoctorSQLiteRepository::getById(const Id &id) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM doctor WHERE id = :id;");
    query.bindValue(":id", id.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getDoctorFromQuery(query);
}

std::optional<Doctor> DoctorSQLiteRepository::getByIdCard(const IdCard &idCard) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM doctor WHERE idCard = :idCard;");
    query.bindValue(":idCard", idCard.getValue());
    query.exec();
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getDoctorFromQuery(query);
}

QList<Doctor> DoctorSQLiteRepository::getAll() const {
    QSqlQuery query(db);
    query.exec("SELECT * FROM doctor;");
    QList<Doctor> que;
    while(query.next())
        que.push_back(DatabaseOperator::getDoctorFromQuery(query));
    return que;
}
