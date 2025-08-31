#ifndef DOCTORFACTORY_H
#define DOCTORFACTORY_H

#include <memory>

#include "doctor.h"
#include "doctorrepository.h"

class DoctorFactory {
public:
    DoctorFactory(std::shared_ptr<DoctorRepository> doctorRepository);

    Doctor createDoctor(Name name, IdCard idCard, Password password) const;

private:
    std::shared_ptr<DoctorRepository> doctorRepository;
};

#endif // DOCTORFACTORY_H
