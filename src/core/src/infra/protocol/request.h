#ifndef REQUEST_H
#define REQUEST_H

#include <optional>
#include <QString>
#include <QJsonObject>

#include "../security/credential.h"

class Request {
public:
    Request(QString endpoint, std::optional<Credential> credential, QJsonObject data):
        endpoint(endpoint), credential(credential), data(data) {}
    QString getEndpoint();
    std::optional<Credential> getCredential();
    QJsonObject getData();
    /*
     * 将endpoint，credential，data包装成JSON并转换为数据流以通过socket发送，
     * 数据流以一个32位无符号整数开头，表示后续JSON数据的长度。
     */
    QByteArray toStream();
private:
    QString endpoint;   //发送的目标端点
    std::optional<Credential> credential; //身份凭证
    QJsonObject data;   //JSON格式数据
};

#endif // REQUEST_H
