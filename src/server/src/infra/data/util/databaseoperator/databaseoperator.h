#ifndef DATABASEOPERATOR_H
#define DATABASEOPERATOR_H

#include "core/src/domain/patient/patient.h"
#include "core/src/domain/doctor/doctor.h"

#include <QtSql>
#include <QString>

class DatabaseOperator
{
public:
    static void createConnection(QSqlDatabase *db, const QString& identifier, const QString& path);
    static void addUserInfo(QSqlQuery *query, const User& user);
    static Patient getPatientFromQuery(const QSqlQuery& query);
    static Doctor getDoctorFromQuery(const QSqlQuery& query);
};

#endif // DATABASEOPERATOR_H
