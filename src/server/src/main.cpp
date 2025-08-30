#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <optional>

#include "infra/data/doctor/doctorsqliterepository.h"
#include "infra/data/util/printer/printer.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    DoctorSQLiteRepository doctorRepository("E:/project/MedicalIntelligence/build/"
    "build-MedicalIntelligence-Desktop_Qt_5_12_8_MinGW_64_bit-Debug/doctor_test.db");
    Doctor user1(Name("张三"),IdCard("111111111111111111"),Password("adeadsdaf"));
    Doctor user2(Name("张五"),IdCard("111141211111111111"),Password("adeadsdaf"));
    user1.setRegistrationFee(RegistrationFee(2.3));
    user1.setDailyPatientLimit(DailyPatientLimit(55));
    user2.setWorkSchedule(WorkSchedule(QTime(8,31),QTime(12,22)));
    user2.setProfile(Profile("这是一个测试"));
    doctorRepository.save(user1);
    doctorRepository.save(user2);
//    qDebug() <<"save over";
    std::optional<Doctor> user3 = doctorRepository.getById(user1.getId());
//    qDebug() <<"over3";
    Printer::printDoctor(user3);
    std::optional<Doctor> user4 = doctorRepository.getByIdCard(user2.getIdCard());
//    qDebug() <<"over4";
    Printer::printDoctor(user4);
    std::optional<Doctor> user5 = doctorRepository.getByIdCard(IdCard("123111000000000031"));
//    qDebug() <<"over5";
    Printer::printDoctor(user5);
    QList<Doctor> que = doctorRepository.getAll();
    qDebug() << "List:";
    for (Doctor ch: que) Printer::printDoctor(ch);
    qDebug() << "end";
    return a.exec();
}
