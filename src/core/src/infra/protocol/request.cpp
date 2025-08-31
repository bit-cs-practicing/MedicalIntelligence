#include "request.h"

#include <QJsonDocument>
#include <QtEndian>

QString Request::getEndpoint() {
    return this->endpoint;
}

std::optional<Credential> Request::getCredential() {
    return this->credential;
}

QJsonObject Request::getData() {
    return this->data;
}

QByteArray Request::toStream() {
    QJsonObject request{
        {"endpoint", this->endpoint.toUtf8().data()},
        {"credential", this->credential.value().toString().toUtf8().data()},
        {"data", this->data}
    };
    QJsonDocument document(request);
    QByteArray jsonData(document.toJson(QJsonDocument::Compact));
    quint32 length = static_cast<quint32>(jsonData.size());
    quint32 networkLength = qToBigEndian(length);
    QByteArray stream;
    stream.append(reinterpret_cast<const char*>(&networkLength), sizeof(length));
    stream.append(jsonData);
    return stream;
}
