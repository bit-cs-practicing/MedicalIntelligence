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
    RpcClient(QHostAddress serverIp, int serverPort);
    void connectServer(QHostAddress serverIp, int serverPort);
    Response rpc(Request request);

private:
    QTcpServer *server = new QTcpServer(this);
    QTcpSocket *client = new QTcpSocket(this);
    bool isConnected = false;
    bool isReady = false;
    Response response = Response::error("timeout");
    ResponseParser parser;
    QTimer timeoutTimer;
    QEventLoop loop;
private slots:
    void slotConnected();
    void slotDisconnected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError error);
    void slotTimeout();
};

#endif // RPCCLIENT_H
