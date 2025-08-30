#ifndef RESPONSE_H
#define RESPONSE_H

#include <QString>
#include <QJsonObject>

class Response {
public:
    bool success;     //是否成功
    QString message;  //（错误）信息
    QJsonObject data; //（成功）JSON格式数据
    Response(bool success, QString message, QJsonObject data):
        success(success), message(message), data(data) {}
    static Response ok();
    static Response ok(QJsonObject);
    static Response error(QString message);
    /*
     * 将success，message，data包装成JSON并转换为数据流以通过socket发送，
     * 数据流以一个32位无符号整数开头，表示后续JSON数据的长度。
     */
    QByteArray toStream();
};

#endif // RESPONSE_H
