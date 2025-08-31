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

#include "infra/data/util/printer/printer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QString path("E:/project/MedicalIntelligence/build/build-MedicalIntelligence-Desktop_Qt_5_12_8_MinGW_64_bit-Debug/doctor_test.db");
    PatientSQLiteRepository patientRepository(path);
    DoctorSQLiteRepository doctorRepository(path);
    AttendanceSQLiteRepository attendanceRepository(path);
    AppointmentSQLiteRepository appointmentSQLiteRepository(path);

    Doctor user1(Name("张三"),IdCard("111111111111111111"),Password("adeadsdaf"));
    Doctor user2(Name("张五"),IdCard("111141211111111111"),Password("adeadsdaf"));
    user1.setRegistrationFee(RegistrationFee(2.3));
    user1.setDailyPatientLimit(DailyPatientLimit(55));
    user2.setWorkSchedule(WorkSchedule(QTime(8,31),QTime(12,22)));
    user2.setProfile(Profile("这是一个测试"));
    doctorRepository.save(user1);
    doctorRepository.save(user2);
    std::optional<Doctor> user3 = doctorRepository.getById(user1.getId());
    Printer::printDoctor(user3);
    std::optional<Doctor> user4 = doctorRepository.getByIdCard(user2.getIdCard());
    Printer::printDoctor(user4);
    std::optional<Doctor> user5 = doctorRepository.getByIdCard(IdCard("123111000000000031"));
    Printer::printDoctor(user5);
    QList<Doctor> que = doctorRepository.getAll();
    qDebug() << "List:";
    for (Doctor ch: que) Printer::printDoctor(ch);
    qDebug() << "end";


    Attendance record1(Id("attendance1"), user1.getId(), QDateTime(QDate(1999,9,9),QTime(22,31,27)));
    Attendance record2(Id("attendance5"), user2.getId(), QDateTime(QDate(2099,2,28),QTime(10,20,17)));
    Attendance record3(Id("attendance6"), user1.getId(), QDateTime(QDate(1009,2,28),QTime(10,20,17)));
    attendanceRepository.save(record1);
    attendanceRepository.save(record2);
    attendanceRepository.save(record3);
    QList<Attendance> Record4 = attendanceRepository.getAllByDoctorId(user1.getId());
    qDebug() << "List:";
    for (auto record: Record4) Printer::printAttendance(record);

    return a.exec();
}
