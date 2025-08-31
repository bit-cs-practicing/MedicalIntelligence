#include "requestparser.h"

#include <QJsonDocument>
#include <QtEndian>

void RequestParser::readSocket(QTcpSocket *socket) {
    buffer.append(socket->readAll());
    while (buffer.size() >= static_cast<int>(sizeof(quint32))) {
        const quint32* lengthPtr = reinterpret_cast<const quint32*>(buffer.constData());
        quint32 length = qFromBigEndian(*lengthPtr);
        if (buffer.size() < static_cast<int>(sizeof (quint32) + length)) {
            break;
        }
        QByteArray jsonData = buffer.mid(sizeof(quint32), length);
        QJsonDocument document = QJsonDocument::fromJson(jsonData);
        completedRequests.enqueue(document.object());
        buffer = buffer.mid(sizeof(quint32) + length);
    }
}

bool RequestParser::hasCompleteRequest() {
    return !completedRequests.isEmpty();
}

Request RequestParser::getNextRequest() {
    QJsonObject jsonRequest(completedRequests.dequeue());
    return Request(jsonRequest.value("endpoint").toString(),
                   Credential::parse(jsonRequest.value("credential").toString()),
                   jsonRequest.value("data").toObject());
}
