#ifndef CASEAPPSERVICE_H
#define CASEAPPSERVICE_H

#include <QJsonObject>

#include "infra/security/credential.h"

class CaseAppService {
public:
    virtual ~CaseAppService() = default;

    virtual QJsonObject create(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject update(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject fetchByAppointment(const QJsonObject& data) const = 0;
    virtual QJsonObject listByPatient(const Credential& credential, const QJsonObject& data) const = 0;
    virtual QJsonObject listByDoctorAndPatient(const Credential& credential, const QJsonObject& data) const = 0;
};

#endif // CASEAPPSERVICE_H
