#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include <QEventLoop>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "infra/protocol/request.h"
#include "infra/protocol/response.h"
#include "infra/protocol/responseparser.h"

class RpcClient: public QObject {
    Q_OBJECT
public:
    RpcClient(QHostAddress serverIp, int serverPort):
        serverIp(serverIp), serverPort(serverPort) {}
    void connectServer(QHostAddress serverIp, int serverPort);
    Response rpc(Request request);

private:
    QHostAddress serverIp;
    int serverPort;
    std::optional<Response> onReadyRead(QTcpSocket *socket, ResponseParser *parser);
};

#endif // RPCCLIENT_H
