#include "databaseoperator.h"

#include <QDebug>
#include <QUuid>
#include <QtSql>

void DatabaseOperator::createConnection(QSqlDatabase *db, const QString& identifier, const QString& path) {
    *db = QSqlDatabase::addDatabase("QSQLITE", identifier + QUuid::createUuid().toString());
    db->setDatabaseName(path);
    if (!db->open()) {
        QString msg = QString("Fail to open the database from %1").arg(path);
        throw std::runtime_error(msg.toStdString());
    }
}

void addUserInfo(QSqlQuery *query, const User& user)
{
    query->bindValue(":id", user.getId().getId());
    query->bindValue(":name", user.getName().getValue());
    query->bindValue(":idCard", user.getIdCard().getValue());
    query->bindValue(":password", user.getPassword().getValue());
}

Patient DatabaseOperator::getPatientFromQuery(const QSqlQuery& query) {
//    qDebug() << "1";
    Name name(query.value(1).toString());
    IdCard idCard(query.value(2).toString());
    Password password(query.value(3).toString());
    Gender gender(query.value(4).toString());
    Phone phone(query.value(5).toString());
    Patient patient(name, idCard, gender, phone, password);
//    qDebug() << "7";

    QVariant birthday = query.value(6);
    if (!birthday.isNull() && birthday.toString() != "")
        patient.setBirthday(Birthday(birthday.toDate()));
//    qDebug() << "9";
    QVariant email = query.value(7);
    if (!email.isNull() && email.toString() != "")
        patient.setEmail(Email(email.toString()));
//    qDebug() << "11";
    QVariant emergencyContact = query.value(8);
    if (!emergencyContact.isNull() && emergencyContact.toString() != "")
        patient.setEmergencyContact(Phone(emergencyContact.toString()));
//    qDebug() << "13";
    return patient;
}
