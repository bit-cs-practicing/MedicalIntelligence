#ifndef ATTENDANCEAPPSERVICE_H
#define ATTENDANCEAPPSERVICE_H

#include <QJsonObject>

#include "infra/security/credential.h"

class AttendanceAppService {
public:
    virtual ~AttendanceAppService() = default;

    virtual QJsonObject checkIn(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject leaveRequest(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject leaveCancel(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject fetchLastRequest(const Credential& credential, const QJsonObject& data) const = 0;
};

#endif // ATTENDANCEAPPSERVICE_H
