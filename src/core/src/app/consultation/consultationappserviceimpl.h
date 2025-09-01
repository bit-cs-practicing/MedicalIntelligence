#ifndef CONSULTATIONAPPSERVICEIMPL_H
#define CONSULTATIONAPPSERVICEIMPL_H

#include <memory>

#include "domain/consultation/consultationanswer.h"
#include "domain/consultation/consultationquestion.h"
#include "domain/consultation/consultationprovider.h"
#include "infra/security/credential.h"
#include "infra/security/credentialregistry.h"

#include "consultationappservice.h"

class ConsultationAppServiceImpl : public ConsultationAppService {
public:
    ConsultationAppServiceImpl(
        std::shared_ptr<ConsultationProvider> patientAssistantProvider,
        std::shared_ptr<ConsultationProvider> doctorAssistantProvider,
        std::shared_ptr<CredentialRegistry> credentialRegistry
    );

    virtual QJsonObject answerForDoctor(const Credential& credential, const QJsonObject& data) const override;
    virtual QJsonObject answerForPatient(const Credential& credential, const QJsonObject& data) const override;
private:
    std::shared_ptr<ConsultationProvider> doctorAssistantProvider;
    std::shared_ptr<ConsultationProvider> patientAssistantProvider;
    std::shared_ptr<CredentialRegistry> credentialRegistry;
};

#endif // CONSULTATIONAPPSERVICEIMPL_H
