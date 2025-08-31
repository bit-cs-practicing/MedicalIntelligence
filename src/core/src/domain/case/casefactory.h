#ifndef CASEFACTORY_H
#define CASEFACTORY_H

#include <memory>

#include "domain/appointment/appointment.h"
#include "domain/doctor/doctor.h"

#include "case.h"

class CaseFactory {
public:
    CaseFactory();

    Case createCase(
        const Doctor& doctor,
        const Appointment& appointment,
        CaseDiagnosis diagnosis,
        CasePrescription prescription,
        CaseAdvice advice
    ) const;
};

#endif // CASEFACTORY_H
