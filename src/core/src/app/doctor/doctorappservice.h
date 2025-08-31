#ifndef DOCTORAPPSERVICE_H
#define DOCTORAPPSERVICE_H

#include <QJsonObject>

#include "infra/security/credential.h"

class DoctorAppService {
public:
    virtual ~DoctorAppService() = default;

    virtual QJsonObject signup(const QJsonObject& data) = 0;
    virtual QJsonObject login(const QJsonObject& data) = 0;
    virtual QJsonObject updateInfo(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject fetchInfo(const QJsonObject& data) const = 0;
    virtual QJsonObject fetchAllInfo(const QJsonObject& data) const = 0;
    virtual QJsonObject updatePassword(const Credential& credential, const QJsonObject& data) = 0;
};

#endif // DOCTORAPPSERVICE_H
