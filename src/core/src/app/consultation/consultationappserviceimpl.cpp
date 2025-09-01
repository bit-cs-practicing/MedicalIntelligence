#include "consultationappserviceimpl.h"

ConsultationAppServiceImpl::ConsultationAppServiceImpl(
    std::shared_ptr<ConsultationProvider> doctorAssistantProvider,
    std::shared_ptr<ConsultationProvider> patientAssistantProvider,
    std::shared_ptr<CredentialRegistry> credentialRegistry
)
    : doctorAssistantProvider(doctorAssistantProvider)
    , patientAssistantProvider(patientAssistantProvider)
    , credentialRegistry(credentialRegistry)
{
}

QJsonObject ConsultationAppServiceImpl::answerForDoctor(const Credential &credential, const QJsonObject &data) const {
    credentialRegistry->check(credential);

    auto question = ConsultationQuestion(data["question"].toString());

    auto answer = doctorAssistantProvider->getAnswer(question);

    return QJsonObject {
        { "answer", answer.getValue() }
    };
}

QJsonObject ConsultationAppServiceImpl::answerForPatient(const Credential &credential, const QJsonObject &data) const {
    credentialRegistry->check(credential);

    auto question = ConsultationQuestion(data["question"].toString());

    auto answer = patientAssistantProvider->getAnswer(question);

    return QJsonObject {
        { "answer", answer.getValue() }
    };
}
