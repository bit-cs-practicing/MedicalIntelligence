#ifndef DATABASEOPERATOR_H
#define DATABASEOPERATOR_H

#include "domain/patient/patient.h"
#include "domain/doctor/doctor.h"
#include "domain/appointment/appointment.h"
#include "domain/attendance/attendance.h"
#include "domain/case/case.h"
#include "domain/leave/leaverecord.h"
#include "domain/message/message.h"

#include <QtSql>

class DatabaseOperator {
public:
    static void createConnection(QSqlDatabase *db, const QString& identifier, const QString& path);
    static void addUserInfo(QSqlQuery *query, const User& user);
    static Patient getPatientFromQuery(const QSqlQuery& query);
    static Doctor getDoctorFromQuery(const QSqlQuery& query);
    static Appointment getAppointmentFromQuery(const QSqlQuery& query);
    static Attendance getAttendanceFromQuery(const QSqlQuery& query);
    static Case getCaseFromQuery(const QSqlQuery& query);
    static LeaveRecord getLeaveRecordFromQuery(const QSqlQuery& query);
    static Message getMessageFromQuery(const QSqlQuery& query);
};

#endif // DATABASEOPERATOR_H
