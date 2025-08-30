#ifndef CASESERVICE_H
#define CASESERVICE_H

#include <memory>
#include <optional>

#include "domain/appointment/appointmentrepository.h"
#include "domain/doctor/doctor.h"

#include "case.h"

class CaseService {
public:
    CaseService(std::shared_ptr<AppointmentRepository> appointmentRepository);

    void updateCase(
        Case* caze,
        const Doctor& doctor,
        std::optional<CaseDiagnosis> diagnosis,
        std::optional<CasePrescription> prescription,
        std::optional<CaseAdvice> advice
    ) const;
private:
    std::shared_ptr<AppointmentRepository> appointmentRepository;
};

#endif // CASESERVICE_H
