#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <optional>

#include "core/src/core.h"
#include "infra/data/patient/patientsqliterepository.h"

void print(const std::optional<Patient>& pt)
{
    if (!pt.has_value()) {
        qDebug() << "User aren't existed";
        return;
    }
    Patient p = pt.value();
    qDebug() << p.getId().getId() << ' ' << p.getName().getValue();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
//    qDebug() << "begin";
    PatientSQLiteRepository patientRepository("E:/project/MedicalIntelligence/build/"
    "build-MedicalIntelligence-Desktop_Qt_5_12_8_MinGW_64_bit-Debug/test.db");
    qDebug() << "begin to create patient";
    Patient user1(Name("张三"),IdCard("111111111111111111"),Gender("male"),Phone("11234567890"),Password("adeadsdaf"));
//    qDebug() << "user1 over";
    Patient user2(Name("张五"),IdCard("111141211111111111"),Gender("female"),Phone("11234567890"),Password("adeadsdaf"));
//    qDebug() << "user2 over";
    user2.setBirthday(Birthday(QDate(1000,1,31)));
//    qDebug() <<"opt1";
    patientRepository.save(user1);
//    qDebug() <<"opt2";
    patientRepository.save(user2);
//    qDebug() <<"save over";
    std::optional<Patient> user3 = patientRepository.getById(user1.getId());
//    qDebug() <<"over3";
    print(user3);
    std::optional<Patient> user4 = patientRepository.getByIdCard(user2.getIdCard());
//    qDebug() <<"over4";
    print(user4);
    std::optional<Patient> user5 = patientRepository.getByIdCard(IdCard("123111000000000031"));
//    qDebug() <<"over5";
    print(user5);
//    qDebug() << "end";
    return a.exec();
}
