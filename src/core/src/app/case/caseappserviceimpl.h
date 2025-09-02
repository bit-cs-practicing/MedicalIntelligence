#ifndef CASEAPPSERVICEIMPL_H
#define CASEAPPSERVICEIMPL_H

#include <memory>

#include "domain/appointment/appointmentrepository.h"
#include "domain/case/casefactory.h"
#include "domain/case/caserepository.h"
#include "domain/case/caseservice.h"
#include "domain/doctor/doctorrepository.h"
#include "infra/security/credentialregistry.h"

#include "caseappservice.h"

class CaseAppServiceImpl : public CaseAppService {
public:
    CaseAppServiceImpl(
        std::shared_ptr<CaseRepository> caseRepository,
        std::shared_ptr<CaseFactory> caseFactory,
        std::shared_ptr<CaseService> caseService,
        std::shared_ptr<AppointmentRepository> appointmentRepository,
        std::shared_ptr<DoctorRepository> doctorRepository,
        std::shared_ptr<CredentialRegistry> credentialRegistry
    );

    virtual QJsonObject create(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject update(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject fetchByAppointment(const QJsonObject& data) const override;
    virtual QJsonObject listByPatient(const Credential& credential, const QJsonObject& data) const override;
    virtual QJsonObject listByDoctorAndPatient(const Credential& credential, const QJsonObject& data) const override;
private:
    std::shared_ptr<CaseRepository> caseRepository;
    std::shared_ptr<CaseFactory> caseFactory;
    std::shared_ptr<CaseService> caseService;
    std::shared_ptr<AppointmentRepository> appointmentRepository;
    std::shared_ptr<DoctorRepository> doctorRepository;
    std::shared_ptr<CredentialRegistry> credentialRegistry;

    static QJsonObject caseToJson(const Case& caze);
};

#endif // CASEAPPSERVICEIMPL_H
