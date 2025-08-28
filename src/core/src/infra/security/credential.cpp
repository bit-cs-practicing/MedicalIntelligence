#include "credential.h"

#include <QUuid>

#include "../../domain/user/user.h"

Credential::Credential(Id userId, QString token): userId(userId), token(token) {
}

Credential Credential::fromUserId(Id userId) {
    QString token = QUuid().toString();
    return Credential(userId, token);
}

const QString& Credential::getUserId() const {
    return userId.getId();
}

QString Credential::getRole() const {
    if (userId.getId().startsWith(User::ROLE_DOCTOR)) {
        return User::ROLE_DOCTOR;
    } else {
        return User::ROLE_PATIENT;
    }
}

QString Credential::toString() const {
    return QString("token:%1+id:%2").arg(token).arg(userId.getId());
}
