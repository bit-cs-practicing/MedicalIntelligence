#include "rpcclient.h"

#include <QJsonDocument>
#include <QThread>

RpcClient::RpcClient(QHostAddress serverIp, int serverPort) {
    connectServer(serverIp, serverPort);
}

void RpcClient::connectServer(QHostAddress serverIp, int serverPort) {
    client->connectToHost(serverIp, serverPort);
    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer, &QTimer::timeout, this, &RpcClient::slotTimeout);
    connect(client, &QAbstractSocket::connected, this, &RpcClient::slotConnected);
    connect(client, &QAbstractSocket::disconnected, this, &RpcClient::slotDisconnected);
    connect(client, &QAbstractSocket::readyRead, this, &RpcClient::slotReadyRead);
    void (QAbstractSocket::*errorSignal)(QAbstractSocket::SocketError) = &QAbstractSocket::error;
    void (RpcClient::*errorSlot)(QAbstractSocket::SocketError) = &RpcClient::slotError;
    connect(client, errorSignal, this, errorSlot);
}

Response RpcClient::rpc(Request request) {
    isReady = false;
    response = Response::error("timeout");
    if (client->write(request.toStream()) < 0) {
        return Response::error("request not sent");
    }
    client->flush();
    timeoutTimer.start(5000);
    loop.exec();
    return response;
}

void RpcClient::slotConnected() {
    isConnected = true;
}

void RpcClient::slotDisconnected() {
    isConnected = false;
}

void RpcClient::slotReadyRead() {
    QTcpSocket *client = qobject_cast<QTcpSocket *>(this->sender());
    parser.readSocket(client);
    if (parser.hasCompleteResponse()) {
        response = parser.getNextResponse();
        isReady = true;
        timeoutTimer.stop();
        loop.quit();
    }
}

void RpcClient::slotError(QAbstractSocket::SocketError error) {
    qDebug() << "error:" << QString(error);
    loop.quit();
}

void RpcClient::slotTimeout() {
    if (!isReady) {
        response = Response::error("timeout");
        loop.quit();
    }
}
