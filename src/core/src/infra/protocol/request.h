#ifndef REQUEST_H
#define REQUEST_H

#include <QString>
#include <QJsonObject>

class Request {
public:
    QString endpoint;   //发送的目标端点
    QString credential; //身份凭证
    QJsonObject data;   //JSON格式数据
    Request(QString endpoint, QString credential, QJsonObject data):
        endpoint(endpoint), credential(credential), data(data) {}
    /*
     * 将endpoint，credential，data包装成JSON并转换为数据流以通过socket发送，
     * 数据流以一个32位无符号整数开头，表示后续JSON数据的长度。
     */
    QByteArray toStream();
};

#endif // REQUEST_H
