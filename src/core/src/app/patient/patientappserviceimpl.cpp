#include "patientappserviceimpl.h"

#include <QDate>

PatientAppServiceImpl::PatientAppServiceImpl(
    std::shared_ptr<PatientRepository> patientRepository,
    std::shared_ptr<PatientFactory> patientFactory,
    std::shared_ptr<PatientService> patientService,
    std::shared_ptr<CredentialRegistry> credentialRegistry
)
    : patientRepository(patientRepository)
    , patientFactory(patientFactory)
    , patientService(patientService)
    , credentialRegistry(credentialRegistry)
{
}

QJsonObject PatientAppServiceImpl::signup(const QJsonObject& data) {
    auto name = Name(data["name"].toString());
    auto password = Password(data["password"].toString());
    auto gender = Gender(data["gender"].toString());
    auto idCard = IdCard(data["idCard"].toString());
    auto phone = Phone(data["phone"].toString());

    std::optional<Birthday> birthday = std::nullopt;
    if (data["birthday"].isString() && !data["birthday"].toString().isEmpty()) {
        birthday = Birthday::parse(data["birthday"].toString());
    }
    std::optional<Email> email = std::nullopt;
    if (data["emial"].isString() && !data["email"].toString().isEmpty()) {
        email = Email(data["email"].toString());
    }
    std::optional<Phone> emergencyContact = std::nullopt;
    if (data["emergencyContact"].isString() && !data["emergencyContact"].toString().isEmpty()) {
        emergencyContact = Phone(data["emergencyContact"].toString());
    }

    auto patient = patientFactory->createPatient(name, idCard, gender, phone, password);
    if (birthday.has_value()) {
        patient.setBirthday(birthday.value());
    }
    if (email.has_value()) {
        patient.setEmail(email.value());
    }
    if (emergencyContact.has_value()) {
        patient.setEmergencyContact(emergencyContact.value());
    }

    patientRepository->save(patient);
    return QJsonObject {
        { "userId", patient.getId().getId() }
    };
}

QJsonObject PatientAppServiceImpl::login(const QJsonObject& data) {
    auto idCard = IdCard(data["idCard"].toString());
    auto password = Password(data["password"].toString());

    auto patientOpt = patientRepository->getByIdCard(idCard);
    if (!patientOpt.has_value()) {
        throw std::logic_error("身份证号未注册");
    }
    auto patient = patientOpt.value();

    patientService->validateLogin(patient, password);

    auto credential = Credential::fromUserId(patient.getId());
    credentialRegistry->add(credential);

    return QJsonObject {
        { "credential", credential.toString() }
    };
}

QJsonObject PatientAppServiceImpl::updateInfo(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto patientId = credential.getUserId();
    auto patientOpt = patientRepository->getById(patientId);
    if (!patientOpt.has_value()) {
        throw std::logic_error("用户 ID 不存在");
    }
    auto patient = patientOpt.value();

    if (data["name"].isString() && !data["name"].toString().isEmpty()) {
        patient.setName(Name(data["name"].toString()));
    }
    if (data["phone"].isString() && !data["phone"].toString().isEmpty()) {
        patient.setPhone(Phone(data["phone"].toString()));
    }
    if (data["gender"].isString() && !data["gender"].toString().isEmpty()) {
        patient.setGender(Gender(data["gender"].toString()));
    }
    if (data["birthday"].isString() && !data["birthday"].toString().isEmpty()) {
        patient.setBirthday(Birthday::parse(data["birthday"].toString()));
    }
    if (data["email"].isString() && !data["email"].toString().isEmpty()) {
        patient.setEmail(Email(data["email"].toString()));
    }
    if (data["emergencyContact"].isString() && !data["emergencyContact"].toString().isEmpty()) {
        patient.setEmergencyContact(Phone(data["emergencyContact"].toString()));
    }

    patientRepository->save(patient);
    return QJsonObject {};
}

QJsonObject PatientAppServiceImpl::fetchInfo(const QJsonObject &data) const {
    auto patientId = Id(data["patientId"].toString());
    auto patientOpt = patientRepository->getById(patientId);
    if (!patientOpt.has_value()) {
        throw std::logic_error("患者 ID 不存在");
    }
    auto patient = patientOpt.value();

    return QJsonObject {
        { "name", patient.getName().getValue() },
        { "gender", patient.getGender().getValue() },
        { "idCard", patient.getIdCard().getValue() },
        { "phone", patient.getPhone().getValue() },
        { "birthday", (patient.getBirthday().has_value() ? patient.getBirthday()->toString() : QJsonValue()) },
        { "email", (patient.getEmail().has_value() ? patient.getEmail()->getValue() : QJsonValue()) },
        { "emergencyContact", (patient.getEmergencyContact().has_value() ? patient.getEmergencyContact()->getValue() : QJsonValue()) }
    };
}

QJsonObject PatientAppServiceImpl::fetchInfoByName(const QJsonObject& data) const {
    auto name = Name(data["name"].toString());
    auto patientOpt = patientRepository->getFirstByName(name);
    if (!patientOpt.has_value()) {
        throw std::logic_error("患者姓名不存在");
    }
    auto patient = patientOpt.value();

    return QJsonObject {
        { "name", patient.getName().getValue() },
        { "gender", patient.getGender().getValue() },
        { "idCard", patient.getIdCard().getValue() },
        { "phone", patient.getPhone().getValue() },
        { "birthday", (patient.getBirthday().has_value() ? patient.getBirthday()->toString() : QJsonValue()) },
        { "email", (patient.getEmail().has_value() ? patient.getEmail()->getValue() : QJsonValue()) },
        { "emergencyContact", (patient.getEmergencyContact().has_value() ? patient.getEmergencyContact()->getValue() : QJsonValue()) }
    };
}
QJsonObject PatientAppServiceImpl::fetchInfoByIdCard(const QJsonObject& data) const {
    auto idCard = IdCard(data["idCard"].toString());
    auto patientOpt = patientRepository->getByIdCard(idCard);
    if (!patientOpt.has_value()) {
        throw std::logic_error("患者身份证号不存在");
    }
    auto patient = patientOpt.value();

    return QJsonObject {
        { "name", patient.getName().getValue() },
        { "gender", patient.getGender().getValue() },
        { "idCard", patient.getIdCard().getValue() },
        { "phone", patient.getPhone().getValue() },
        { "birthday", (patient.getBirthday().has_value() ? patient.getBirthday()->toString() : QJsonValue()) },
        { "email", (patient.getEmail().has_value() ? patient.getEmail()->getValue() : QJsonValue()) },
        { "emergencyContact", (patient.getEmergencyContact().has_value() ? patient.getEmergencyContact()->getValue() : QJsonValue()) }
    };
}

QJsonObject PatientAppServiceImpl::updatePassword(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto patientId = credential.getUserId();
    auto patientOpt = patientRepository->getById(patientId);
    if (!patientOpt.has_value()) {
        throw std::logic_error("患者 ID 不存在");
    }
    auto patient = patientOpt.value();

    auto oldPassword = Password(data["oldPassword"].toString());
    auto newPassword = Password(data["newPassword"].toString());
    patientService->updatePassword(&patient, oldPassword, newPassword);

    patientRepository->save(patient);
    return QJsonObject {};
}
