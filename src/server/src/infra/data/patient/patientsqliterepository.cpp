#include "patientsqliterepository.h"

#include <QUuid>
#include <QVariant>
#include <exception>
#include <QtSql/QSqlQuery>
#include <QDebug>

PatientSQLiteRepository::PatientSQLiteRepository(const QString& path) {
    db = QSqlDatabase::addDatabase("QSQLITE", "Patient" + QUuid::createUuid().toString());
    db.setDatabaseName(path);
//    qDebug() << "set over";
    if (!db.open()) {
        QString msg = QString("Fail to open the database from %1").arg(path);
        throw std::runtime_error(msg.toStdString());
    }
//    qDebug() << "over";
}

Patient getPatientFromQuery(const QSqlQuery& query) {
//    qDebug() << "1";
    Name name(query.value(1).toString());
//    qDebug() << "2";
    IdCard idCard(query.value(2).toString());
//    qDebug() << "3";
    Password password(query.value(3).toString());
//    qDebug() << "4";
    Gender gender(query.value(4).toString());
//    qDebug() << "5";
    Phone phone(query.value(5).toString());
//    qDebug() << "6";
    Patient patient(name, idCard, gender, phone, password);
//    qDebug() << "7";

    QVariant birthday = query.value(6);
//    qDebug() << "8";
    if (!birthday.isNull() && birthday.toString() != "") patient.setBirthday(Birthday(birthday.toDate()));
//    qDebug() << "9";
    QVariant email = query.value(7);
//    qDebug() << "10";
    if (!email.isNull() && email.toString() != "") patient.setEmail(Email(email.toString()));
//    qDebug() << "11";
    QVariant emergencyContact = query.value(8);
//    qDebug() << "12";
    if (!emergencyContact.isNull() && emergencyContact.toString() != "") patient.setEmergencyContact(Phone(emergencyContact.toString()));
//    qDebug() << "13";
    return patient;
}

//void print(const std::optional<Patient>&);

void PatientSQLiteRepository::save(const Patient &patient) {
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO patient(id,name,idCard,password,"
        "gender,phone,birthday,email,emergencyContact) "
        "VALUES (:id,:name,:idCard,:password,"
        ":gender,:phone,:birthday,:email,:emergencyContact);"
    );

    query.bindValue(":id", patient.getId().getId());
    query.bindValue(":name", patient.getName().getValue());
    query.bindValue(":idCard", patient.getIdCard().getValue());
    query.bindValue(":password", patient.getPassword().getValue());
    query.bindValue(":gender", patient.getGender().getValue());
    query.bindValue(":phone", patient.getPhone().getValue());
    if (patient.getBirthday().has_value())
        query.bindValue(":birthday", patient.getBirthday()->getValue().toString());
    else query.bindValue(":birthday", "");
    if (patient.getEmail().has_value())
        query.bindValue(":email", patient.getEmail()->getValue());
    else query.bindValue(":email", "");
    if (patient.getEmergencyContact().has_value())
        query.bindValue(":emergencyContact", patient.getEmergencyContact()->getValue());
    else query.bindValue(":emergencyContact", "");
//    qDebug() << query.lastQuery();
    bool result = query.exec();
//    qDebug() << query.lastQuery();
//    if (result) qDebug() << "success";
//    else qDebug() << "fail";
}

std::optional<Patient> PatientSQLiteRepository::getById(const Id &id) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM patient WHERE id = :id;");
    query.bindValue(":id", id.getId());
    bool result = query.exec();
//    if (result) qDebug() << "success";
//    else qDebug() << "fail";
//    qDebug() << "!";
    if (!query.next()) return std::nullopt;
    return getPatientFromQuery(query);
}

std::optional<Patient> PatientSQLiteRepository::getByIdCard(const IdCard &idCard) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM patient WHERE idCard = :idCard;");
    query.bindValue(":idCard", idCard.getValue());
    query.exec();
    if (!query.next()) return std::nullopt;
    return getPatientFromQuery(query);
}

PatientSQLiteRepository::~PatientSQLiteRepository() {
    db.close();
}
