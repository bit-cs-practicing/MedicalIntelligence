#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include "domain/user/password.h"

#include "doctor.h"

class DoctorService {
public:
    DoctorService();

    void validateLogin(const Doctor& doctor, const Password& password) const;
    void updatePassword(Doctor* doctor, const Password& oldPassword, Password newPassword) const;
};

#endif // DOCTORSERVICE_H
