#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <iostream>
#include <optional>

#include "infra/data/patient/patientsqliterepository.h"
#include "infra/data/doctor/doctorsqliterepository.h"
#include "infra/data/appointment/appointmentsqliterepository.h"
#include "infra/data/attendance/attendancesqliterepository.h"

#include "infra/data/leave/leaverecordsqliterepository.h"

#include "infra/data/util/printer/printer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QString path("E:/project/MedicalIntelligence/build/build-MedicalIntelligence-Desktop_Qt_5_12_8_MinGW_64_bit-Debug/schema.db");
    PatientSQLiteRepository patientRepository(path);
    DoctorSQLiteRepository doctorRepository(path);
    AttendanceSQLiteRepository attendanceRepository(path);
    AppointmentSQLiteRepository appointmentRepository(path);

    LeaveRecordSQLiteRepository leaveRecordRepository(path);

    Patient patient1(Name("吴三"),IdCard("111111111111152111"),Gender("male"),Phone("11234567890"),Password("adeadsdaf"));
    Patient patient2(Name("刘五"),IdCard("111141211232111111"),Gender("female"),Phone("11234567890"),Password("adeadsdaf"));
    patient1.setEmail(Email("3@162.com"));
    patient2.setBirthday(Birthday(QDate(1000,1,31)));
    patientRepository.save(patient1);
    patientRepository.save(patient2);
    std::optional<Patient> patient3 = patientRepository.getById(patient1.getId());
    Printer::printPatient(patient3);
    std::optional<Patient> patient4 = patientRepository.getByIdCard(patient2.getIdCard());
    Printer::printPatient(patient4);
    std::optional<Patient> patient5 = patientRepository.getFirstByName(Name("吴三"));
    Printer::printPatient(patient5);

    Doctor doctor1(Name("张三"),IdCard("111111111111111111"),Password("adeadsdaf"));
    Doctor doctor2(Name("张五"),IdCard("111141211111111111"),Password("adeadsdaf"));
    doctor1.setRegistrationFee(RegistrationFee(2.3));
    doctor1.setDailyPatientLimit(DailyPatientLimit(55));
    doctor2.setWorkSchedule(WorkSchedule(QTime(8,31),QTime(12,22)));
    doctor2.setProfile(Profile("这是一个测试"));
    doctorRepository.save(doctor1);
    doctorRepository.save(doctor2);
    std::optional<Doctor> doctor3 = doctorRepository.getById(doctor1.getId());
    Printer::printDoctor(doctor3);
    std::optional<Doctor> doctor4 = doctorRepository.getByIdCard(doctor2.getIdCard());
    Printer::printDoctor(doctor4);
    QList<Doctor> Doctor5 = doctorRepository.getAll();
    qDebug() << "List:";
    for (Doctor doctor: Doctor5) Printer::printDoctor(doctor);

    Attendance attendance1(Id("attendance1"), doctor1.getId(), QDateTime(QDate(1999,9,9),QTime(22,31,27)));
    Attendance attendance2(Id("attendance5"), doctor2.getId(), QDateTime(QDate(2099,2,28),QTime(10,20,17)));
    Attendance attendance3(Id("attendance6"), doctor1.getId(), QDateTime(QDate(1009,2,28),QTime(10,20,17)));
    attendanceRepository.save(attendance1);
    attendanceRepository.save(attendance2);
    attendanceRepository.save(attendance3);
    QList<Attendance> Attendance4 = attendanceRepository.getAllByDoctorId(doctor1.getId());
    qDebug() << "List:";
    for (auto attendance: Attendance4) Printer::printAttendance(attendance);
    std::optional<Attendance> attendance5 = attendanceRepository.getLastByDoctorIdOrderedByTime(doctor1.getId());
    Printer::printAttendance(attendance5);
    std::optional<Attendance> attendance6 = attendanceRepository.getById(attendance2.getAttendanceId());
    Printer::printAttendance(attendance6);

    Appointment appointment1(Id("appointment1"),doctor1.getId(),patient2.getId(),
                             QDate(2025,9,1),AppointmentTimeSlot(QTime(12,30),QTime(13,20)));
    Appointment appointment2(Id("appointment2"),doctor2.getId(),patient2.getId(),
                             QDate(2025,9,2),AppointmentTimeSlot(QTime(13,30),QTime(14,20)));
    Appointment appointment3(Id("appointment3"),doctor1.getId(),patient1.getId(),
                             QDate(2025,9,3),AppointmentTimeSlot(QTime(12,30),QTime(15,20)));
    Appointment appointment4(Id("appointment4"),doctor2.getId(),patient1.getId(),
                             QDate(2025,9,4),AppointmentTimeSlot(QTime(12,30),QTime(15,20)));
    Appointment appointment5(Id("appointment5"),doctor1.getId(),patient2.getId(),
                             QDate(2025,9,1),AppointmentTimeSlot(QTime(13,30),QTime(15,20)));
    Appointment appointment6(Id("appointment6"),doctor1.getId(),patient1.getId(),
                             QDate(2025,9,1),AppointmentTimeSlot(QTime(12,30),QTime(15,20)));
    appointmentRepository.save(appointment1);
    appointmentRepository.save(appointment2);
    appointmentRepository.save(appointment3);
    appointmentRepository.save(appointment4);
    appointmentRepository.save(appointment5);
    appointmentRepository.save(appointment6);
    std::optional<Appointment> appointment7 = appointmentRepository.getById(appointment1.getAppointmentId());
    Printer::printAppointment(appointment7);
    QList<Appointment> Appointnment1 = appointmentRepository.getAllByDoctorId(doctor2.getId());
    qDebug() << "List:";
    for (auto appointment: Appointnment1) Printer::printAppointment(appointment);
    QList<Appointment> Appointnment2 = appointmentRepository.getAllByPatientId(patient1.getId());
    qDebug() << "List:";
    for (auto appointment: Appointnment2) Printer::printAppointment(appointment);
    QList<Appointment> Appointnment3 = appointmentRepository.getAllByDoctorIdAndPatientId(doctor1.getId(),patient2.getId());
    qDebug() << "List:";
    for (auto appointment: Appointnment3) Printer::printAppointment(appointment);
    QList<Appointment> Appointnment4 = appointmentRepository.getAllByDoctorIdAndDate(doctor1.getId(),QDate(2025,9,1));
    qDebug() << "List:";
    for (auto appointment: Appointnment4) Printer::printAppointment(appointment);

    LeaveRecord record1(Id("record1"),doctor1.getId(),
                        LeavePeriod(QDateTime(QDate(2025,9,1),QTime(12,30,29)),
                                    QDateTime(QDate(2025,9,3),QTime(12,30,29))));
    record1.cancelLeave();
    LeaveRecord record2(Id("record2"),doctor1.getId(),
                        LeavePeriod(QDateTime(QDate(2025,9,2),QTime(12,30,29)),
                                    QDateTime(QDate(2025,9,4),QTime(12,30,29))));
    leaveRecordRepository.save(record1);
    leaveRecordRepository.save(record2);
    std::optional<LeaveRecord> record3 = leaveRecordRepository.getById(Id("record1"));
    Printer::printLeaveRecord(record3);
    std::optional<LeaveRecord> record4 = leaveRecordRepository.getLastByDoctorId(doctor1.getId());
    Printer::printLeaveRecord(record4);

    return a.exec();
}
