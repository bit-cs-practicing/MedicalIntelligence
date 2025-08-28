#ifndef CASEREPOSITORY_H
#define CASEREPOSITORY_H

#include "case.h"
#include <optional>

class CaseRepository {
public:
    virtual ~CaseRepository() = 0;

    virtual void save(const Case& caseEntity) = 0;
    virtual std::optional<Case> getById(const Id& caseId) = 0;
    virtual std::optional<Case> getByAppointmentId(const Id& appointmentId) = 0;
};

#endif // CASEREPOSITORY_H
