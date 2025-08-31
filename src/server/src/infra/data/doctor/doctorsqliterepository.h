#ifndef DOCTORSQLITEREPOSITORY_H
#define DOCTORSQLITEREPOSITORY_H

#include <optional>

#include <QString>
#include <QtSql/QSqlDatabase>

#include "domain/doctor/doctorrepository.h"

class DoctorSQLiteRepository : public DoctorRepository {
public:
    DoctorSQLiteRepository(const QString& path);
    ~DoctorSQLiteRepository();
    void save(const Doctor& doctor) override;
    std::optional<Doctor> getById(const Id &id) const override;
    std::optional<Doctor> getByIdCard(const IdCard &idCard) const override;
    QList<Doctor> getAll() const override;
private:
    QSqlDatabase db;
};

#endif // DOCTORSQLITEREPOSITORY_H
