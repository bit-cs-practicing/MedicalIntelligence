#ifndef PATIENTAPPSERVICEIMPL_H
#define PATIENTAPPSERVICEIMPL_H

#include <memory>

#include "domain/patient/patient.h"
#include "domain/patient/patientfactory.h"
#include "domain/patient/patientrepository.h"
#include "domain/patient/patientservice.h"
#include "infra/security/credential.h"
#include "infra/security/credentialregistry.h"

#include "patientappservice.h"

class PatientAppServiceImpl : public PatientAppService {
public:
    PatientAppServiceImpl(
        std::shared_ptr<PatientRepository> patientRepository,
        std::shared_ptr<PatientFactory> patientFactory,
        std::shared_ptr<PatientService> patientService,
        std::shared_ptr<CredentialRegistry> credentialRegistry
    );

    virtual QJsonObject signup(const QJsonObject& data) override;
    virtual QJsonObject login(const QJsonObject& data) override;
    virtual QJsonObject updateInfo(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject fetchInfo(const QJsonObject& data) const override;
    virtual QJsonObject fetchInfoByName(const QJsonObject& data) const override;
    virtual QJsonObject fetchInfoByIdCard(const QJsonObject& data) const override;
    virtual QJsonObject updatePassword(const Credential& credential, const QJsonObject& data) override;
private:
    std::shared_ptr<PatientRepository> patientRepository;
    std::shared_ptr<PatientFactory> patientFactory;
    std::shared_ptr<PatientService> patientService;
    std::shared_ptr<CredentialRegistry> credentialRegistry;
};

#endif // PATIENTAPPSERVICEIMPL_H
