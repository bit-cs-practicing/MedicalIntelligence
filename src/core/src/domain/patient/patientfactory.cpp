#include "patientfactory.h"

PatientFactory::PatientFactory(std::shared_ptr<PatientRepository> patientRepository)
    : patientRepository(std::move(patientRepository)) {}

Patient PatientFactory::createPatient(Name name, IdCard idCard, Gender gender, Phone phone, Password password) const {
    auto existingPatient = patientRepository->getByIdCard(idCard);
    if (existingPatient.has_value()) {
        throw std::logic_error("已有相同身份证号的患者");
    }
    return Patient(name, idCard, gender, phone, password);
}
