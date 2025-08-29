#ifndef PATIENTREPOSITORY_H
#define PATIENTREPOSITORY_H

#include "patient.h"
#include <optional>

class PatientRepository {
public:
    virtual ~PatientRepository() = default;

    virtual void save(const Patient& patient) = 0;

    virtual std::optional<Patient> getById(const Id& id) const = 0;
    virtual std::optional<Patient> getByIdCard(const IdCard& idCard) const = 0;
};

#endif // PATIENTREPOSITORY_H
