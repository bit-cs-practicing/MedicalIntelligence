#ifndef DOCTORSQLITEREPOSITORY_H
#define DOCTORSQLITEREPOSITORY_H

#include "domain/doctor/doctorrepository.h"

#include <QtSql>

class DoctorSQLiteRepository : public DoctorRepository {
public:
    DoctorSQLiteRepository(const QUrl& path);
    ~DoctorSQLiteRepository();
    void save(const Doctor& doctor) override;
    std::optional<Doctor> getById(const Id &id) const override;
    std::optional<Doctor> getByIdCard(const IdCard &idCard) const override;
    QList<Doctor> getAll() const override;
private:
    QSqlDatabase db;
};

#endif // DOCTORSQLITEREPOSITORY_H
