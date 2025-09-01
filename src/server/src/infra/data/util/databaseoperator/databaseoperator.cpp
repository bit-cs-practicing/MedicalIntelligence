#include "databaseoperator.h"

#include <QDebug>
#include <QtSql>
#include <QUrl>
#include <QUuid>

void DatabaseOperator::createConnection(QSqlDatabase *db, const QString& identifier, const QString& path) {
    *db = QSqlDatabase::addDatabase("QSQLITE", identifier + QUuid::createUuid().toString());
    db->setDatabaseName(path);
    qDebug() << path;
    if (!db->open()) {
        QString msg = QString("Fail to open the database from %1").arg(path);
        qDebug() << msg;
        qDebug() << db->lastError().text();
        throw std::runtime_error(msg.toStdString());
    }
}

void DatabaseOperator::addUserInfo(QSqlQuery *query, const User& user) {
    query->bindValue(":id", user.getId().getId());
    query->bindValue(":name", user.getName().getValue());
    query->bindValue(":idCard", user.getIdCard().getValue());
    query->bindValue(":password", user.getPassword().getValue());
}

bool isEmpty(const QVariant& obj) {
    return obj.isNull() || obj.toString() == "";
}

Patient DatabaseOperator::getPatientFromQuery(const QSqlQuery& query) {
    Name name(query.value(1).toString());
    IdCard idCard(query.value(2).toString());
    Password password(query.value(3).toString());
    Gender gender(query.value(4).toString());
    Phone phone(query.value(5).toString());
    Patient patient(name, idCard, gender, phone, password);

    QVariant birthday = query.value(6);
    if (!isEmpty(birthday))
        patient.setBirthday(Birthday(birthday.toDate()));

    QVariant email = query.value(7);
    if (!isEmpty(email))
        patient.setEmail(Email(email.toString()));
    QVariant emergencyContact = query.value(8);
    if (!isEmpty(emergencyContact))
        patient.setEmergencyContact(Phone(emergencyContact.toString()));
    return patient;
}

Doctor DatabaseOperator::getDoctorFromQuery(const QSqlQuery& query) {
    Name name(query.value(1).toString());
    IdCard idCard(query.value(2).toString());
    Password password(query.value(3).toString());
    Doctor doctor(name, idCard, password);

    QVariant employeeId = query.value(4);
    if (!isEmpty(employeeId))
        doctor.setEmployeeId(EmployeeId(employeeId.toString()));
    QVariant department = query.value(5);
    if (!isEmpty(department))
        doctor.setDepartment(Department(department.toString()));
    QVariant profile = query.value(6);
    if (!isEmpty(profile))
        doctor.setProfile(Profile(profile.toString()));
    QVariant photo = query.value(7);
    if (!isEmpty(photo))
        doctor.setPhoto(QUrl(photo.toString()));

    QVariant startTime = query.value(8);
    QVariant endTime = query.value(9);
    if (!isEmpty(startTime) && !isEmpty(endTime))
        doctor.setWorkSchedule(WorkSchedule(startTime.toTime(), endTime.toTime()));

    QVariant registrationFee = query.value(10);
    if (!isEmpty(registrationFee))
        doctor.setRegistrationFee(RegistrationFee(registrationFee.toReal()));
    QVariant dailyPatientLimit = query.value(11);
    if (!isEmpty(dailyPatientLimit))
        doctor.setDailyPatientLimit(DailyPatientLimit(dailyPatientLimit.toInt()));
    return doctor;
}

Appointment DatabaseOperator::getAppointmentFromQuery(const QSqlQuery& query) {
    Id appointmentId(query.value(0).toString());
    Id doctorId(query.value(1).toString());
    Id patientId(query.value(2).toString());
    QDate date(query.value(3).toDate());
    QTime startTime(query.value(4).toTime());
    QTime endTime(query.value(5).toTime());
    AppointmentStatus status(query.value(6).toString());
    Appointment appointment(appointmentId,doctorId,patientId,date,AppointmentTimeSlot(startTime,endTime));
    if (status.getValue() == AppointmentStatus::COMPLETED)
        appointment.markAsCompleted();
    if (status.getValue() == AppointmentStatus::CANCELLED)
        appointment.markAsCancelled();
    return appointment;
}

Attendance DatabaseOperator::getAttendanceFromQuery(const QSqlQuery& query) {
    Id attendanceId(query.value(0).toString());
    Id doctorId(query.value(1).toString());
    QDateTime attendanceTime(query.value(2).toDateTime());
    return Attendance(attendanceId, doctorId, attendanceTime);
}

Case DatabaseOperator::getCaseFromQuery(const QSqlQuery& query) {
    Id caseId(query.value(0).toString());
    Id appointmentId(query.value(1).toString());
    CaseDiagnosis diagnosis(query.value(2).toString());
    CasePrescription prescription(query.value(3).toString());
    CaseAdvice advice(query.value(4).toString());
    QDate visitDate(query.value(5).toDate());
    return Case(caseId,appointmentId,diagnosis,prescription,advice,visitDate);
}

LeaveRecord DatabaseOperator::getLeaveRecordFromQuery(const QSqlQuery& query) {
    Id leaveId(query.value(0).toString());
    Id doctorId(query.value(1).toString());
    QDateTime startTime(query.value(2).toDateTime());
    QDateTime endTime(query.value(3).toDateTime());
    LeaveRecord leaveRecord(leaveId,doctorId,LeavePeriod(startTime,endTime));
    QString status(query.value(4).toString());
    if (status == LeaveStatus::CANCELED)
        leaveRecord.cancelLeave();
    return leaveRecord;
}

Message DatabaseOperator::getMessageFromQuery(const QSqlQuery& query) {
    Id messageId(query.value(0).toString());
    Id topicId(query.value(1).toString());
    Id senderId(query.value(2).toString());
    Name senderName(query.value(3).toString());
    MessageContent content(query.value(4).toString());
    QDateTime sendTime(query.value(5).toDateTime());
    return Message(messageId,topicId,senderId,senderName,content,sendTime);
}
