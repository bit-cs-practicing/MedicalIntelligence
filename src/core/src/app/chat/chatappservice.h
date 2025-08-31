#ifndef CHATAPPSERVICE_H
#define CHATAPPSERVICE_H

#include <QJsonObject>

#include "infra/security/credential.h"

class ChatAppService {
public:
    virtual ~ChatAppService() = default;

    virtual QJsonObject createTopic(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject listTopicsByUser(const Credential& credential, const QJsonObject& data) const = 0;
    virtual QJsonObject sendMessage(const Credential& credential, const QJsonObject& data) = 0;
    virtual QJsonObject fetchMessages(const Credential& credential, const QJsonObject& data) const = 0;
};

#endif // CHATAPPSERVICE_H
