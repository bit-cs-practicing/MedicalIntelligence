#include "appointmentappserviceimpl.h"

#include <QJsonArray>

AppointmentAppServiceImpl::AppointmentAppServiceImpl(
    std::shared_ptr<AppointmentRepository> appointmentRepository,
    std::shared_ptr<AppointmentFactory> appointmentFactory,
    std::shared_ptr<AppointmentService> appointmentService,
    std::shared_ptr<PatientRepository> patientRepository,
    std::shared_ptr<DoctorRepository> doctorRepository,
    std::shared_ptr<CredentialRegistry> credentialRegistry
)
    : appointmentRepository(appointmentRepository)
    , appointmentFactory(appointmentFactory)
    , appointmentService(appointmentService)
    , patientRepository(patientRepository)
    , doctorRepository(doctorRepository)
    , credentialRegistry(credentialRegistry)
{
}

QJsonObject AppointmentAppServiceImpl::create(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto patientId = Id(credential.getUserId());
    auto patientOpt = patientRepository->getById(patientId);
    if (!patientOpt.has_value()) {
        throw std::logic_error("无效患者登录凭证");
    }
    auto patient = patientOpt.value();

    auto doctorId = Id(data["doctorId"].toString());
    auto doctorOpt = doctorRepository->getById(patientId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("不存在此医生 ID");
    }
    auto doctor = doctorOpt.value();

    auto date = QDate::fromString(data["date"].toString(), "yyyy-MM-dd");
    auto timeSlot = AppointmentTimeSlot::parse(data["timeSlot"].toString());

    auto appointment = appointmentFactory->createAppointment(doctor, patient, date, timeSlot);
    appointmentRepository->save(appointment);

    return QJsonObject {
        { "appointmentId", appointment.getAppointmentId().getId() }
    };
}

QJsonObject AppointmentAppServiceImpl::cancel(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto patientId = Id(credential.getUserId());
    auto patientOpt = patientRepository->getById(patientId);
    if (!patientOpt.has_value()) {
        throw std::logic_error("无效患者登录凭证");
    }
    auto patient = patientOpt.value();

    auto appointmentId = Id(data["appointmentId"].toString());
    auto appointmentOpt = appointmentRepository->getById(appointmentId);
    if (!appointmentOpt.has_value()) {
        throw std::logic_error("不存在此预约");
    }
    auto appointment = appointmentOpt.value();

    appointmentService->cancelAppointment(&appointment, patient);
    appointmentRepository->save(appointment);

    return QJsonObject {};
}

QJsonObject AppointmentAppServiceImpl::complete(const Credential &credential, const QJsonObject &data) {
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

    appointmentService->completeAppointment(&appointment, doctor);
    appointmentRepository->save(appointment);

    return QJsonObject {};
}

QJsonObject AppointmentAppServiceImpl::listByPatient(const Credential &credential, const QJsonObject &) const {
    credentialRegistry->check(credential);

    auto patientId = Id(credential.getUserId());
    if (!patientRepository->getById(patientId).has_value()) {
        throw std::logic_error("无效患者登录凭证");
    }

    auto appointments = appointmentRepository->getAllByPatientId(patientId);
    auto appointmentsJson = QJsonArray();
    for (const auto& appointment : appointments) {
        auto appointmentJson = AppointmentAppServiceImpl::appointmentToJson(appointment);
        appointmentsJson.push_back(appointmentJson);
    }

    return QJsonObject {
        { "appointments", appointmentsJson }
    };
}

QJsonObject AppointmentAppServiceImpl::listByDoctor(const Credential &credential, const QJsonObject &) const {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    if (!doctorRepository->getById(doctorId).has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }

    auto appointments = appointmentRepository->getAllByDoctorId(doctorId);
    auto appointmentsJson = QJsonArray();
    for (const auto& appointment : appointments) {
        auto appointmentJson = AppointmentAppServiceImpl::appointmentToJson(appointment);
        appointmentsJson.push_back(appointmentJson);
    }

    return QJsonObject {
        { "appointments", appointmentsJson }
    };
}

QJsonObject AppointmentAppServiceImpl::appointmentToJson(const Appointment& appointment)  {
    return QJsonObject {
        { "appointmentId", appointment.getAppointmentId().getId() },
        { "patientId", appointment.getPatientId().getId() },
        { "date", appointment.getDate().toString("yyyy-MM-dd") },
        { "timeSlot", appointment.getTimeSlot().toString() },
        { "status", appointment.getStatus().getValue() }
    };
}

