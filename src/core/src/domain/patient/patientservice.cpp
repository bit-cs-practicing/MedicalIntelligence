#include "patientservice.h"

#include <stdexcept>

PatientService::PatientService() {

}

void PatientService::validateLogin(const Patient& patient, const Password& password) const {
    if (patient.getPassword().getValue() != password.getValue()) {
        throw std::logic_error("密码不正确，登录失败");
    }
}

void PatientService::updatePassword(Patient *patient, const Password &oldPassword, Password newPassword) const {
    assert(patient != nullptr);
    if (patient->getPassword().getValue() != oldPassword.getValue()) {
        throw std::logic_error("密码不正确，无法修改密码");
    }
    patient->setPassword(std::move(newPassword));
}
