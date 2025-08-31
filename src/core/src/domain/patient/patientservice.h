#ifndef PATIENTSERVICE_H
#define PATIENTSERVICE_H

#include "domain/user/password.h"

#include "patient.h"

class PatientService {
public:
    PatientService();

    void validateLogin(const Patient& patient, const Password& password) const;
    void updatePassword(Patient* patient, const Password& oldPassword, Password newPassword) const;
};

#endif // PATIENTSERVICE_H
