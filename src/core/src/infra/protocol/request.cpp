#include "request.h"

#include <QJsonDocument>
#include <QtEndian>

const QString& Request::getEndpoint() const {
    return this->endpoint;
}

std::optional<Credential> Request::getCredential() const {
    return this->credential;
}

const QJsonObject& Request::getData() const {
    return this->data;
}

QByteArray Request::toStream() {
    auto credentialVal = "";
    if (this->credential.has_value()) {
        credentialVal = this->credential.value().toString().toUtf8().data();
    }
    QJsonObject request{
        {"endpoint", this->endpoint.toUtf8().data()},
        {"credential", credentialVal},
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
