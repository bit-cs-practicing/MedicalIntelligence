#include "doctor.h"

Doctor::Doctor(Name name, IdCard idCard, Password password)
    : User(name, idCard, password)
    , employeeId(std::nullopt)
    , department(std::nullopt)
    , profile(std::nullopt)
    , workSchedule(std::nullopt)
    , registrationFee(std::nullopt)
    , dailyPatientLimit(std::nullopt)
{
}

const std::optional<EmployeeId>& Doctor::getEmployeeId() const {
    return employeeId;
}

void Doctor::setEmployeeId(EmployeeId value) {
    employeeId = std::make_optional(value);
}

const std::optional<Department>& Doctor::getDepartment() const {
    return department;
}

void Doctor::setDepartment(Department value) {
    department = std::make_optional(value);
}

const std::optional<Profile>& Doctor::getProfile() const {
    return profile;
}

void Doctor::setProfile(Profile value) {
    profile = std::make_optional(value);
}

void Doctor::setPhoto(QUrl value) {
    photo = std::make_optional(value);
}

const std::optional<QUrl> &Doctor::getPhoto() const {
    return photo;
}

const std::optional<WorkSchedule>& Doctor::getWorkSchedule() const {
    return workSchedule;
}

void Doctor::setWorkSchedule(WorkSchedule value) {
    workSchedule = std::make_optional(value);
}

const std::optional<RegistrationFee>& Doctor::getRegistrationFee() const {
    return registrationFee;
}

void Doctor::setRegistrationFee(RegistrationFee value) {
    registrationFee = std::make_optional(value);
}

const std::optional<DailyPatientLimit>& Doctor::getDailyPatientLimit() const {
    return dailyPatientLimit;
}

void Doctor::setDailyPatientLimit(DailyPatientLimit value) {
    dailyPatientLimit = std::make_optional(value);
}

QString Doctor::getRole() const {
    return User::ROLE_DOCTOR;
}
