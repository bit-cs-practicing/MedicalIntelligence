#ifndef CONSULTATIONAPPSERVICE_H
#define CONSULTATIONAPPSERVICE_H

#include <QJsonObject>

#include "infra/security/credential.h"

class ConsultationAppService {
public:
    virtual ~ConsultationAppService() = default;

    virtual QJsonObject answerForPatient(const Credential& credential, const QJsonObject& data) const = 0;
    virtual QJsonObject answerForDoctor(const Credential& credential, const QJsonObject& data) const = 0;
};

#endif // CONSULTATIONAPPSERVICE_H
