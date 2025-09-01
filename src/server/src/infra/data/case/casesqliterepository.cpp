#include "casesqliterepository.h"

#include <QDebug>

#include "infra/data/util/databaseoperator/databaseoperator.h"

CaseSQLiteRepository::CaseSQLiteRepository(const QString& path) {
    DatabaseOperator::createConnection(&db, "Case", path);
}

CaseSQLiteRepository::~CaseSQLiteRepository() {
    db.close();
}

void CaseSQLiteRepository::save(const Case &caseEntity) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM cases WHERE caseId = :caseId;");
    query.bindValue(":caseId", caseEntity.getCaseId().getId());
    DatabaseOperator::execOperation(&query);

    query.prepare(
        "INSERT INTO cases(caseId,appointmentId,diagnosis,prescription,advice,visitDate) "
        "VALUES (:caseId,:appointmentId,:diagnosis,:prescription,:advice,:visitDate);"
    );
    query.bindValue(":caseId", caseEntity.getCaseId().getId());
    query.bindValue(":appointmentId", caseEntity.getAppointmentId().getId());
    query.bindValue(":diagnosis", caseEntity.getDiagnosis().getValue());
    query.bindValue(":prescription", caseEntity.getPrescription().getValue());
    query.bindValue(":advice", caseEntity.getAdvice().getValue());
    query.bindValue(":visitDate", caseEntity.getVisitDate().toString(Qt::ISODate));
    DatabaseOperator::execOperation(&query);
}

std::optional<Case> CaseSQLiteRepository::getById(const Id& caseId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM cases WHERE caseId = :caseId;");
    query.bindValue(":caseId", caseId.getId());
    DatabaseOperator::execOperation(&query);
    if (!query.next()) {
        return std::nullopt;
    }
    return DatabaseOperator::getCaseFromQuery(query);
}

std::optional<Case> CaseSQLiteRepository::getByAppointmentId(const Id& appointmentId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM cases WHERE appointmentId = :appointmentId;");
    query.bindValue(":appointmentId", appointmentId.getId());
    DatabaseOperator::execOperation(&query);
    if (!query.next()) {
        return std::nullopt;
    }
    return DatabaseOperator::getCaseFromQuery(query);
}
