#ifndef APPOINTMENTAPPSERVICEIMPL_H
#define APPOINTMENTAPPSERVICEIMPL_H

#include <memory>

#include "domain/appointment/appointment.h"
#include "domain/appointment/appointmentfactory.h"
#include "domain/appointment/appointmentrepository.h"
#include "domain/appointment/appointmentservice.h"
#include "domain/doctor/doctor.h"
#include "domain/doctor/doctorrepository.h"
#include "domain/patient/patient.h"
#include "domain/patient/patientrepository.h"
#include "infra/security/credentialregistry.h"

#include "appointmentappservice.h"

class AppointmentAppServiceImpl : public AppointmentAppService {
public:
    AppointmentAppServiceImpl(
        std::shared_ptr<AppointmentRepository> appointmentRepository,
        std::shared_ptr<AppointmentFactory> appointmentFactory,
        std::shared_ptr<AppointmentService> appointmentService,
        std::shared_ptr<PatientRepository> patientRepository,
        std::shared_ptr<DoctorRepository> doctorRepository,
        std::shared_ptr<CredentialRegistry> credentialRegistry
    );

    virtual QJsonObject create(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject cancel(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject complete(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject listByPatient(const Credential& credential, const QJsonObject& data) const override;
    virtual QJsonObject listByDoctor(const Credential& credential, const QJsonObject& data) const override;
private:
    std::shared_ptr<AppointmentRepository> appointmentRepository;
    std::shared_ptr<AppointmentFactory> appointmentFactory;
    std::shared_ptr<AppointmentService> appointmentService;
    std::shared_ptr<PatientRepository> patientRepository;
    std::shared_ptr<DoctorRepository> doctorRepository;
    std::shared_ptr<CredentialRegistry> credentialRegistry;

    static QJsonObject appointmentToJson(const Appointment& appointment);
};

#endif // APPOINTMENTAPPSERVICEIMPL_H
