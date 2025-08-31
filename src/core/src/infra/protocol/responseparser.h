#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

#include <QByteArray>
#include <QJsonObject>
#include <QQueue>
#include <QTcpSocket>

#include "response.h"

class ResponseParser {
public:
    void readSocket(QTcpSocket *socket);
    bool hasCompleteResponse();
    Response getNextResponse();
private:
    QByteArray buffer;
    QQueue<QJsonObject> completedResponses;
};

#endif // RESPONSEPARSER_H
