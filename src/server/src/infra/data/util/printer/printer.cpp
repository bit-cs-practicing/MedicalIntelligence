#include "printer.h"

#include <QDebug>
#include <QString>

void Printer::printPatient(const std::optional<Patient>& obj) {
    if (!obj.has_value()) {
        qDebug() << "Patient aren't existed";
        return;
    }
    Patient p = obj.value();
    qDebug() << p.getId().getId() << '|' << p.getName().getValue() << '|'
             << p.getIdCard().getValue() << '|' << p.getGender().getValue() << '|'
             << p.getPhone().getValue();
}

void Printer::printDoctor(const std::optional<Doctor>& obj) {
    if (!obj.has_value()) {
        qDebug() << "Doctor aren't existed";
        return;
    }
    Doctor p = obj.value();
    QString profile("");
    if (p.getProfile().has_value()) profile = p.getProfile()->getValue();
    QString startTime(""), endTime("");
    if (p.getWorkSchedule().has_value()) {
        startTime = p.getWorkSchedule()->getStartTime().toString();
        endTime = p.getWorkSchedule()->getEndTime().toString();
    }
    double fee = -1;
    if (p.getRegistrationFee().has_value()) fee = p.getRegistrationFee()->getValue();
    int limit = -1;
    if (p.getDailyPatientLimit().has_value()) limit = p.getDailyPatientLimit()->getValue();

    qDebug() << p.getId().getId() << '|' << p.getName().getValue() << '|'
             << p.getIdCard().getValue() << '|' << profile << '|'
             << startTime << '|' << endTime << '|'
             << fee << '|' << limit;
}

void Printer::printAttendance(const std::optional<Attendance>& obj) {
    if (!obj.has_value()) {
        qDebug() << "Attendance aren't existed";
        return;
    }
    Attendance p = obj.value();
    qDebug() << p.getAttendanceId().getId() << '|' << p.getDoctorId().getId() << '|'
             << p.getAttendanceTime().toString(Qt::ISODate);
}

void Printer::printAppointment(const std::optional<Appointment>& obj) {
    if (!obj.has_value()) {
        qDebug() << "Appointment aren't existed";
        return;
    }
    static const QString format("hh:mm:ss");
    Appointment p = obj.value();
    qDebug() << p.getAppointmentId().getId() << '|' << p.getDoctorId().getId() << '|'
             << p.getPatientId().getId() << '|' << p.getDate().toString(Qt::ISODate) << '|'
             << p.getTimeSlot().getStartTime().toString(format) << '|'
             << p.getTimeSlot().getEndTime().toString(format) << '|'
             << p.getStatus().getValue();
}
