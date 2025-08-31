#include "doctorappserviceimpl.h"

#include <optional>

#include <QJsonArray>

DoctorAppServiceImpl::DoctorAppServiceImpl(
    std::shared_ptr<DoctorRepository> doctorRepository,
    std::shared_ptr<DoctorFactory> doctorFactory,
    std::shared_ptr<DoctorService> doctorService,
    std::shared_ptr<CredentialRegistry> credentialRegistry
)
    : doctorRepository(doctorRepository)
    , doctorFactory(doctorFactory)
    , doctorService(doctorService)
    , credentialRegistry(credentialRegistry)
{
}

QJsonObject DoctorAppServiceImpl::signup(const QJsonObject& data) {
    auto name = Name(data["name"].toString());
    auto password = Password(data["password"].toString());
    auto idCard = IdCard(data["idCard"].toString());

    std::optional<EmployeeId> employeeId = std::nullopt;
    if (data["employeeId"].isString() && !data["employeeId"].toString().isEmpty()) {
        employeeId = EmployeeId(data["employeeId"].toString());
    }
    std::optional<Department> department = std::nullopt;
    if (data["department"].isString() && !data["department"].toString().isEmpty()) {
        department = Department(data["department"].toString());
    }
    std::optional<Profile> profile = std::nullopt;
    if (data["profile"].isString() && !data["profile"].toString().isEmpty()) {
        profile = Profile(data["profile"].toString());
    }
    std::optional<QUrl> photo = std::nullopt;
    if (data["photo"].isString() && !data["photo"].toString().isEmpty()) {
        photo = QUrl(data["photo"].toString());
    }
    std::optional<WorkSchedule> workSchedule = std::nullopt;
    if (data["workSchedule"].isString() && !data["workSchedule"].toString().isEmpty()) {
        workSchedule = WorkSchedule::fromString(data["workSchedule"].toString());
    }
    std::optional<RegistrationFee> registrationFee = std::nullopt;
    if (data["registrationFee"].isDouble()) {
        registrationFee = RegistrationFee(data["registrationFee"].toDouble());
    }
    std::optional<DailyPatientLimit> dailyPatientLimit = std::nullopt;
    if (data["dailyPatientLimit"].isDouble()) {
        dailyPatientLimit = DailyPatientLimit(data["dailyPatientLimit"].toInt());
    }

    auto doctor = doctorFactory->createDoctor(name, idCard, password);
    if (employeeId.has_value()) {
        doctor.setEmployeeId(employeeId.value());
    }
    if (department.has_value()) {
        doctor.setDepartment(department.value());
    }
    if (profile.has_value()) {
        doctor.setProfile(profile.value());
    }
    if (photo.has_value()) {
        doctor.setPhoto(photo.value());
    }
    if (workSchedule.has_value()) {
        doctor.setWorkSchedule(workSchedule.value());
    }
    if (registrationFee.has_value()) {
        doctor.setRegistrationFee(registrationFee.value());
    }
    if (dailyPatientLimit.has_value()) {
        doctor.setDailyPatientLimit(dailyPatientLimit.value());
    }

    doctorRepository->save(doctor);
    return QJsonObject {
        { "userId", doctor.getId().getId() }
    };
}

QJsonObject DoctorAppServiceImpl::login(const QJsonObject& data) {
    auto idCard = IdCard(data["idCard"].toString());
    auto password = Password(data["password"].toString());

    auto doctorOpt = doctorRepository->getByIdCard(idCard);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("身份证号未注册，不存在此医生账号");
    }
    auto doctor = doctorOpt.value();

    doctorService->validateLogin(doctor, password);

    auto credential = Credential::fromUserId(doctor.getId());
    credentialRegistry->add(credential);

    return QJsonObject {
        { "credential", credential.toString() }
    };
}

QJsonObject DoctorAppServiceImpl::updateInfo(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto doctorId = credential.getUserId();
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("医生 ID 不存在");
    }
    auto doctor = doctorOpt.value();

    if (data["name"].isString() && !data["name"].toString().isEmpty()) {
        doctor.setName(Name(data["name"].toString()));
    }
    if (data["employeeId"].isString() && !data["employeeId"].toString().isEmpty()) {
        doctor.setEmployeeId(EmployeeId(data["employeeId"].toString()));
    }
    if (data["department"].isString() && !data["department"].toString().isEmpty()) {
        doctor.setDepartment(Department(data["department"].toString()));
    }
    if (data["profile"].isString() && !data["profile"].toString().isEmpty()) {
        doctor.setProfile(Profile(data["profile"].toString()));
    }
    if (data["photo"].isString() && !data["photo"].toString().isEmpty()) {
        doctor.setPhoto(QUrl(data["photo"].toString()));
    }
    if (data["workSchedule"].isString() && !data["workSchedule"].toString().isEmpty()) {
        doctor.setWorkSchedule(WorkSchedule::fromString(data["workSchedule"].toString()));
    }
    if (data["registrationFee"].isDouble()) {
        doctor.setRegistrationFee(RegistrationFee(data["registrationFee"].toDouble()));
    }
    if (data["dailyPatientLimit"].isDouble()) {
        doctor.setDailyPatientLimit(DailyPatientLimit(data["dailyPatientLimit"].toInt()));
    }

    doctorRepository->save(doctor);
    return QJsonObject {};
}

QJsonObject DoctorAppServiceImpl::fetchInfo(const QJsonObject &data) const {
    auto doctorId = Id(data["doctorId"].toString());
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("医生 ID 不存在");
    }
    auto doctor = doctorOpt.value();

    return QJsonObject {
        { "doctorId", doctor.getId().getId() },
        { "name", doctor.getName().getValue() },
        { "idCard", doctor.getIdCard().getValue() },
        { "employeeId", (doctor.getEmployeeId().has_value() ? doctor.getEmployeeId()->getValue() : QJsonValue()) },
        { "department", (doctor.getDepartment().has_value() ? doctor.getDepartment()->getValue() : QJsonValue()) },
        { "profile", (doctor.getProfile().has_value() ? doctor.getProfile()->getValue() : QJsonValue()) },
        { "photo", (doctor.getPhoto().has_value() ? doctor.getPhoto()->toString() : QJsonValue()) },
        { "workSchedule", (doctor.getWorkSchedule().has_value() ? doctor.getWorkSchedule()->toString() : QJsonValue()) },
        { "registrationFee", (doctor.getRegistrationFee().has_value() ? doctor.getRegistrationFee()->getValue() : QJsonValue()) },
        { "dailyPatientLimit", (doctor.getDailyPatientLimit().has_value() ? doctor.getDailyPatientLimit()->getValue() : QJsonValue()) }
    };
}

QJsonObject DoctorAppServiceImpl::fetchAllInfo(const QJsonObject &) const {
    auto doctors = doctorRepository->getAll();
    auto doctorsJson = QJsonArray();

    for (const auto& doctor : doctors) {
        auto doctorJson = QJsonObject {
            { "doctorId", doctor.getId().getId() },
            { "name", doctor.getName().getValue() },
            { "idCard", doctor.getIdCard().getValue() },
            { "employeeId", (doctor.getEmployeeId().has_value() ? doctor.getEmployeeId()->getValue() : QJsonValue()) },
            { "department", (doctor.getDepartment().has_value() ? doctor.getDepartment()->getValue() : QJsonValue()) },
            { "profile", (doctor.getProfile().has_value() ? doctor.getProfile()->getValue() : QJsonValue()) },
            { "photo", (doctor.getPhoto().has_value() ? doctor.getPhoto()->toString() : QJsonValue()) },
            { "workSchedule", (doctor.getWorkSchedule().has_value() ? doctor.getWorkSchedule()->toString() : QJsonValue()) },
            { "registrationFee", (doctor.getRegistrationFee().has_value() ? doctor.getRegistrationFee()->getValue() : QJsonValue()) },
            { "dailyPatientLimit", (doctor.getDailyPatientLimit().has_value() ? doctor.getDailyPatientLimit()->getValue() : QJsonValue()) }
        };
        doctorsJson.push_back(doctorJson);
    }

    return QJsonObject {
        { "doctors", doctorsJson }
    };
}

QJsonObject DoctorAppServiceImpl::updatePassword(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto doctorId = credential.getUserId();
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("医生 ID 不存在");
    }
    auto doctor = doctorOpt.value();

    auto oldPassword = Password(data["oldPassword"].toString());
    auto newPassword = Password(data["newPassword"].toString());
    doctorService->updatePassword(&doctor, oldPassword, newPassword);

    doctorRepository->save(doctor);
    return QJsonObject {};
}

