#ifndef CASEFACTORY_H
#define CASEFACTORY_H

#include <memory>

#include "case.h"
#include "../doctor/doctor.h"
#include "../appointment/appointment.h"

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
