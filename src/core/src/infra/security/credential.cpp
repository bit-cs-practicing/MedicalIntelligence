#include "credential.h"

#include <QUuid>
#include <QStringList>

#include "../../domain/user/user.h"

Credential::Credential(Id userId, QString token): userId(userId), token(token) {
}

Credential Credential::fromUserId(Id userId) {
    QString token = QUuid().toString();
    return Credential(userId, token);
}


Credential Credential::parse(QString str) {
    QStringList parts = str.split("+");
    if (parts.size() != 2) {
        throw std::invalid_argument("无效登录凭证");
    }
    QString tokenPart = parts[0];
    QString idPart = parts[1];
    if (!tokenPart.startsWith("token:") || !idPart.startsWith("id:")) {
        throw std::invalid_argument("无效登录凭证");
    }
    QString token = tokenPart.mid(6);
    Id userId = Id(idPart.mid(3));
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
