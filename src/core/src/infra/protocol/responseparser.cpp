#include "responseparser.h"

#include <QJsonDocument>
#include <QtEndian>

void ResponseParser::readSocket(QTcpSocket *socket) {
    buffer.append(socket->readAll());
    while (buffer.size() >= static_cast<int>(sizeof(quint32))) {
        const quint32* lengthPtr = reinterpret_cast<const quint32*>(buffer.constData());
        quint32 length = qFromBigEndian(*lengthPtr);
        if (buffer.size() < static_cast<int>(sizeof (quint32) + length)) {
            break;
        }
        QByteArray jsonData = buffer.mid(sizeof(quint32), length);
        QJsonDocument document = QJsonDocument::fromJson(jsonData);
        completedResponses.enqueue(document.object());
        buffer = buffer.mid(sizeof(quint32) + length);
    }
}

bool ResponseParser::hasCompleteResponse() {
    return !completedResponses.isEmpty();
}

Response ResponseParser::getNextResponse() {
    QJsonObject jsonResponse(completedResponses.dequeue());
    return Response(jsonResponse.value("success").toBool(),
                   jsonResponse.value("message").toString(),
                   jsonResponse.value("data").toObject());
}
