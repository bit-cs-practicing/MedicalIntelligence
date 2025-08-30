#include "databaseoperator.h"

#include <QDebug>
#include <QUuid>
#include <QtSql>
#include <QUrl>

void DatabaseOperator::createConnection(QSqlDatabase *db, const QString& identifier, const QString& path) {
    *db = QSqlDatabase::addDatabase("QSQLITE", identifier + QUuid::createUuid().toString());
    db->setDatabaseName(path);
    if (!db->open()) {
        QString msg = QString("Fail to open the database from %1").arg(path);
        throw std::runtime_error(msg.toStdString());
    }
}

void DatabaseOperator::addUserInfo(QSqlQuery *query, const User& user)
{
    query->bindValue(":id", user.getId().getId());
    query->bindValue(":name", user.getName().getValue());
    query->bindValue(":idCard", user.getIdCard().getValue());
    query->bindValue(":password", user.getPassword().getValue());
}

bool isEmpty(const QVariant& obj) {return obj.isNull() || obj.toString() == "";}

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
