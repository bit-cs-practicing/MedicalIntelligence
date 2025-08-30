#ifndef CASEREPOSITORY_H
#define CASEREPOSITORY_H

#include <optional>

#include "case.h"

class CaseRepository {
public:
    virtual ~CaseRepository() = default;

    virtual void save(const Case& caseEntity) = 0;
    virtual std::optional<Case> getById(const Id& caseId) const = 0;
    virtual std::optional<Case> getByAppointmentId(const Id& appointmentId) const = 0;
};

#endif // CASEREPOSITORY_H
