#ifndef DOCTOR_H
#define DOCTOR_H

#include <optional>
#include <QUrl>

#include "../user/user.h"
#include "employeeid.h"
#include "department.h"
#include "profile.h"
#include "workschedule.h"
#include "registrationfee.h"
#include "dailypatientlimit.h"

class Doctor : public User {
public:
    Doctor(Name name, IdCard idCard, Password password);

    const std::optional<EmployeeId>& getEmployeeId() const;
    void setEmployeeId(EmployeeId value);

    const std::optional<Department>& getDepartment() const;
    void setDepartment(Department value);

    const std::optional<Profile>& getProfile() const;
    void setProfile(Profile value);

    const std::optional<QUrl>& getPhoto() const;
    void setPhoto(QUrl value);

    const std::optional<WorkSchedule>& getWorkSchedule() const;
    void setWorkSchedule(WorkSchedule value);

    const std::optional<RegistrationFee>& getRegistrationFee() const;
    void setRegistrationFee(RegistrationFee value);

    const std::optional<DailyPatientLimit>& getDailyPatientLimit() const;
    void setDailyPatientLimit(DailyPatientLimit value);

    virtual QString getRole() const override;
private:
    std::optional<EmployeeId> employeeId;
    std::optional<Department> department;
    std::optional<Profile> profile;
    std::optional<QUrl> photo;
    std::optional<WorkSchedule> workSchedule;
    std::optional<RegistrationFee> registrationFee;
    std::optional<DailyPatientLimit> dailyPatientLimit;
};

#endif // DOCTOR_H
