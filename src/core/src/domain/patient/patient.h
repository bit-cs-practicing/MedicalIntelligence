#ifndef PATIENT_H
#define PATIENT_H

#include <optional>

#include "../user/user.h"
#include "birthday.h"
#include "email.h"
#include "gender.h"
#include "phone.h"

class Patient : public User {
public:
    Patient(Name name, IdCard idCard, Gender gender, Phone phone, Password password);

    const Gender& getGender() const;
    void setGender(Gender value);

    const Phone& getPhone() const;
    void setPhone(Phone value);

    const std::optional<Birthday>& getBirthday() const;
    void setBirthday(Birthday value);

    const std::optional<Email>& getEmail() const;
    void setEmail(Email value);

    const std::optional<Phone>& getEmergencyContact() const;
    void setEmergencyContact(Phone value);

    virtual QString getRole() const override;
private:
    Gender gender;
    Phone phone;
    std::optional<Birthday> birthday;
    std::optional<Email> email;
    std::optional<Phone> emergencyContact;
};

#endif // PATIENT_H
