#include "patientsqliterepository.h"

#include <QDebug>
#include <QVariant>

#include "infra/data/util/databaseoperator/databaseoperator.h"

PatientSQLiteRepository::PatientSQLiteRepository(const QString& path) {
    DatabaseOperator::createConnection(&db, "Patient", path);
}

PatientSQLiteRepository::~PatientSQLiteRepository() {
    db.close();
}

void PatientSQLiteRepository::save(const Patient &patient) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM patient WHERE id = :id;");
    query.bindValue(":id", patient.getId().getId());
    DatabaseOperator::execOperation(&query);

    query.prepare(
        "INSERT INTO patient(id,name,idCard,password,"
        "gender,phone,birthday,email,emergencyContact) "
        "VALUES (:id,:name,:idCard,:password,"
        ":gender,:phone,:birthday,:email,:emergencyContact);"
    );
    DatabaseOperator::addUserInfo(&query, patient);
    query.bindValue(":gender", patient.getGender().getValue());
    query.bindValue(":phone", patient.getPhone().getValue());
    if (patient.getBirthday().has_value()) {
        query.bindValue(":birthday", patient.getBirthday()->getValue().toString(Qt::ISODate));
    } else {
        query.bindValue(":birthday", "");
    }
    if (patient.getEmail().has_value()) {
        query.bindValue(":email", patient.getEmail()->getValue());
    } else {
        query.bindValue(":email", "");
    }
    if (patient.getEmergencyContact().has_value()) {
        query.bindValue(":emergencyContact", patient.getEmergencyContact()->getValue());
    } else {
        query.bindValue(":emergencyContact", "");
    }
    DatabaseOperator::execOperation(&query);
}

std::optional<Patient> PatientSQLiteRepository::getById(const Id &id) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM patient WHERE id = :id;");
    query.bindValue(":id", id.getId());
    DatabaseOperator::execOperation(&query);
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getPatientFromQuery(query);
}

std::optional<Patient> PatientSQLiteRepository::getByIdCard(const IdCard &idCard) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM patient WHERE idCard = :idCard;");
    query.bindValue(":idCard", idCard.getValue());
    DatabaseOperator::execOperation(&query);
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getPatientFromQuery(query);
}

std::optional<Patient> PatientSQLiteRepository::getFirstByName(const Name &name) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM patient WHERE name = :name;");
    query.bindValue(":name", name.getValue());
    DatabaseOperator::execOperation(&query);
    if (!query.next()) return std::nullopt;
    return DatabaseOperator::getPatientFromQuery(query);
}
