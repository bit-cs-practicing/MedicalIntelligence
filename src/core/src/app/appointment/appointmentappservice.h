#ifndef APPOINTMENTAPPSERVICE_H
#define APPOINTMENTAPPSERVICE_H

#include <QJsonObject>

#include "infra/security/credential.h"

class AppointmentAppService {
public:
    virtual ~AppointmentAppService() = default;

    virtual QJsonObject create(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject cancel(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject complete(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject listByPatient(const Credential& credential, const QJsonObject& data) const = 0;
    virtual QJsonObject listByDoctor(const Credential& credential, const QJsonObject& data) const = 0;
};

#endif // APPOINTMENTAPPSERVICE_H
