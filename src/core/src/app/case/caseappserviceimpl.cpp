#include "caseappserviceimpl.h"

#include <QJsonArray>

CaseAppServiceImpl::CaseAppServiceImpl(
    std::shared_ptr<CaseRepository> caseRepository,
    std::shared_ptr<CaseFactory> caseFactory,
    std::shared_ptr<CaseService> caseService,
    std::shared_ptr<AppointmentRepository> appointmentRepository,
    std::shared_ptr<DoctorRepository> doctorRepository,
    std::shared_ptr<CredentialRegistry> credentialRegistry
)
    : caseRepository(std::move(caseRepository))
    , caseFactory(std::move(caseFactory))
    , caseService(std::move(caseService))
    , appointmentRepository(std::move(appointmentRepository))
    , doctorRepository(std::move(doctorRepository))
    , credentialRegistry(std::move(credentialRegistry))
{
}

QJsonObject CaseAppServiceImpl::create(const Credential& credential, const QJsonObject& data) {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }
    auto doctor = doctorOpt.value();

    auto appointmentId = Id(data["appointmentId"].toString());
    auto appointmentOpt = appointmentRepository->getById(appointmentId);
    if (!appointmentOpt.has_value()) {
        throw std::logic_error("不存在此预约");
    }
    auto appointment = appointmentOpt.value();

    auto diagnosis = CaseDiagnosis(data["diagnosis"].toString());
    auto prescription = CasePrescription(data["prescription"].toString());
    auto advice = CaseAdvice(data["advice"].toString());

    auto caze = caseFactory->createCase(doctor, appointment, diagnosis, prescription, advice);
    caseRepository->save(caze);

    return QJsonObject {
        { "caseId", caze.getCaseId().getId() }
    };
}

QJsonObject CaseAppServiceImpl::update(const Credential& credential, const QJsonObject& data) {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }
    auto doctor = doctorOpt.value();

    auto caseId = Id(data["caseId"].toString());
    auto caseOpt = caseRepository->getById(caseId);
    if (!caseOpt.has_value()) {
        throw std::logic_error("病例不存在");
    }
    auto caze = caseOpt.value();

    std::optional<CaseDiagnosis> diagnosis;
    if (data["diagnosis"].isString() && !data["diagnosis"].toString().isEmpty()) {
        diagnosis = CaseDiagnosis(data["diagnosis"].toString());
    }
    std::optional<CasePrescription> prescription;
    if (data["prescription"].isString() && !data["prescription"].toString().isEmpty()) {
        prescription = CasePrescription(data["prescription"].toString());
    }
    std::optional<CaseAdvice> advice;
    if (data["advice"].isString() && !data["advice"].toString().isEmpty()) {
        advice = CaseAdvice(data["advice"].toString());
    }

    caseService->updateCase(&caze, doctor, diagnosis, prescription, advice);
    caseRepository->save(caze);

    return QJsonObject {};
}

QJsonObject CaseAppServiceImpl::fetchByAppointment(const QJsonObject& data) const {
    auto appointmentId = Id(data["appointmentId"].toString());

    auto caseOpt = caseRepository->getByAppointmentId(appointmentId);
    if (!caseOpt.has_value()) {
        throw std::logic_error("病例不存在");
    }
    auto caze = caseOpt.value();

    return CaseAppServiceImpl::caseToJson(caze);
}

QJsonObject CaseAppServiceImpl::listByPatient(const Credential& credential, const QJsonObject&) const {
    credentialRegistry->check(credential);

    auto patientId = Id(credential.getUserId());
    auto appointments = appointmentRepository->getAllByPatientId(patientId);

    auto casesJson = QJsonArray();
    for (const auto& appointment : appointments) {
        auto caseOpt = caseRepository->getByAppointmentId(appointment.getAppointmentId());
        if (!caseOpt.has_value()) {
            continue;
        }
        auto caze = caseOpt.value();
        auto caseJson = CaseAppServiceImpl::caseToJson(caze);
        casesJson.push_back(caseJson);
    }

    return QJsonObject {
        { "cases", casesJson }
    };
}

QJsonObject CaseAppServiceImpl::listByDoctorAndPatient(const Credential& credential, const QJsonObject& data) const {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    auto patientId = Id(data["patientId"].toString());
    auto appointments = appointmentRepository->getAllByPatientId(patientId);

    auto casesJson = QJsonArray();
    for (const auto& appointment : appointments) {
        auto caseOpt = caseRepository->getByAppointmentId(appointment.getAppointmentId());
        if (!caseOpt.has_value()) {
            continue;
        }
        auto caze = caseOpt.value();
        auto caseJson = CaseAppServiceImpl::caseToJson(caze);
        casesJson.push_back(caseJson);
    }

    return QJsonObject {
        { "cases", casesJson }
    };
}

QJsonObject CaseAppServiceImpl::caseToJson(const Case& caze) {
    return QJsonObject {
        { "caseId", caze.getCaseId().getId() },
        { "visitDate", caze.getVisitDate().toString("yyyy-MM-dd") },
        { "diagnosis", caze.getDiagnosis().getValue() },
        { "prescription", caze.getPrescription().getValue() },
        { "advice", caze.getAdvice().getValue() }
    };
}

