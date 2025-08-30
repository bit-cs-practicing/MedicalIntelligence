#include "response.h"

#include <QJsonDocument>
#include <QtEndian>

Response Response::ok() {
    return Response(true, "成功", {});
}

Response Response::ok(QJsonObject data) {
    return Response(true, "成功", data);
}

Response Response::error(QString message) {
    return Response(false, message, {});
}

QByteArray Response::toStream() {
    QJsonObject response{
        {"success", this->success},
        {"message", this->message.toUtf8().data()},
        {"data", this->data}
    };
    QJsonDocument document(response);
    QByteArray jsonData(document.toJson(QJsonDocument::Compact));
    quint32 length = static_cast<quint32>(jsonData.size());
    quint32 networkLength = qToBigEndian(length);
    QByteArray stream;
    stream.append(reinterpret_cast<const char*>(&networkLength), sizeof(length));
    stream.append(jsonData);
    return stream;
}
