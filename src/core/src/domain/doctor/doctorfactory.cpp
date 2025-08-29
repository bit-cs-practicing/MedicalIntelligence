#include "doctorfactory.h"

DoctorFactory::DoctorFactory(std::shared_ptr<DoctorRepository> doctorRepository)
    : doctorRepository(std::move(doctorRepository)) {}

Doctor DoctorFactory::createDoctor(Name name, IdCard idCard, Password password) const {
    auto existingDoctor = doctorRepository->getByIdCard(idCard);
    if (existingDoctor.has_value()) {
        throw std::logic_error("已有相同身份证号的医生");
    }
    return Doctor(name, idCard, password);
}
