#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QEventLoop>

#include "../protocol/request.h"
#include "../protocol/response.h"
#include "../protocol/responseparser.h"

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

#endif // CLIENT_H
