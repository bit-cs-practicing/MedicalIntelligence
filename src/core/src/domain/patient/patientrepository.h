#ifndef PATIENTREPOSITORY_H
#define PATIENTREPOSITORY_H

#include "patient.h"
#include <optional>

class PatientRepository {
public:
    virtual ~PatientRepository() = 0;

    virtual void save(const Patient& patient) = 0;

    virtual std::optional<Patient> getById(const Id& id) = 0;
    virtual std::optional<Patient> getByIdCard(const IdCard& idCard) = 0;
};

#endif // PATIENTREPOSITORY_H
