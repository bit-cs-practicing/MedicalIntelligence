#ifndef PATIENTSQLITEREPOSITORY_H
#define PATIENTSQLITEREPOSITORY_H

#include "domain/patient/patientrepository.h"

#include <QtSql>

class PatientSQLiteRepository : public PatientRepository {
public:
    PatientSQLiteRepository(const QUrl& path);
    ~PatientSQLiteRepository();
    void save(const Patient& patient) override;
    std::optional<Patient> getById(const Id &id) const override;
    std::optional<Patient> getByIdCard(const IdCard &idCard) const override;
    std::optional<Patient> getFirstByName(const Name &name) const override;
private:
    QSqlDatabase db;
};

#endif // PATIENTSQLITEREPOSITORY_H
