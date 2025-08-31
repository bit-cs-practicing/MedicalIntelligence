#ifndef CASESQLITEREPOSITORY_H
#define CASESQLITEREPOSITORY_H

#include "domain/case/caserepository.h"

#include <QtSql>

class CaseSQLiteRepository : public CaseRepository
{
public:
    CaseSQLiteRepository(const QString& path);
    ~CaseSQLiteRepository();
    void save(const Case& caseEntity) override;
    std::optional<Case> getById(const Id& caseId) const override;
    std::optional<Case> getByAppointmentId(const Id& appointmentId) const override;
private:
    QSqlDatabase db;
};

#endif // CASESQLITEREPOSITORY_H
