#include "doctorservice.h"

#include <cassert>
#include <stdexcept>

DoctorService::DoctorService() {

}


void DoctorService::validateLogin(const Doctor& doctor, const Password& password) const {
    if (doctor.getPassword().getValue() != password.getValue()) {
        throw std::logic_error("登录失败");
    }
}

void DoctorService::updatePassword(Doctor* doctor, const Password& oldPassword, Password newPassword) const {
    assert(doctor != nullptr);
    if (doctor->getPassword().getValue() != oldPassword.getValue()) {
        throw std::logic_error("密码不正确，无法修改密码");
    }
    doctor->setPassword(std::move(newPassword));
}
