#ifndef PATIENTFACTORY_H
#define PATIENTFACTORY_H

#include <memory>

#include "patientrepository.h"

class PatientFactory {
public:
    PatientFactory(std::shared_ptr<PatientRepository> patientRepository);

    Patient createPatient(Name name, IdCard idCard, Gender gender, Phone phone, Password password) const;
private:
    std::shared_ptr<PatientRepository> patientRepository;
};

#endif // PATIENTFACTORY_H
