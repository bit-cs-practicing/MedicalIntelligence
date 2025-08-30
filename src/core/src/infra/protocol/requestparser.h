#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <QByteArray>
#include <QJsonObject>
#include <QTcpSocket>
#include <QQueue>

#include "request.h"

class RequestParser {
public:
    void readSocket(QTcpSocket *socket);
    bool hasCompleteRequest();
    Request getNextRequest();
private:
    QByteArray buffer;
    QQueue<QJsonObject> completedRequests;
};

#endif // REQUESTPARSER_H
