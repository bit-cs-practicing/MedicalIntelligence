#include "rpcserver.h"

#include <QDebug>

RpcServer::RpcServer(std::unique_ptr<RpcController> rpcController, QObject* parent)
    : QTcpServer(parent), rpcController(std::move(rpcController))
{
}

void RpcServer::incomingConnection(qintptr socketDescriptor) {
    auto carrier = new Carrier(socketDescriptor, rpcController.get());
    executor.start(carrier);
}

Carrier::Carrier(qintptr socketDescriptor, RpcController* rpcController)
    : socketDescriptor(socketDescriptor), rpcController(rpcController)
{
}

void Carrier::run() {
    auto task = std::make_unique<TaskSocket>(socketDescriptor, rpcController);
    qDebug() << QString("%1:%2").arg(task->peerAddress().toString()).arg(task->peerPort());
    int retry = 10;
    while (task->isOpen() && retry > 0) {
        retry -= 1;
        if (task->waitForReadyRead(2000) && task->isOpen()) {
            task->onReadyRead();
        }
    }

}

TaskSocket::TaskSocket(qintptr socketDescriptor, RpcController* rpcController):
    rpcController(rpcController)
{
    setSocketDescriptor(socketDescriptor);
    connect(this, &QAbstractSocket::readyRead, this, &TaskSocket::onReadyRead);
    connect(this, &QAbstractSocket::disconnected, this, [&]() {
        qDebug() << "disconnected";
        deleteLater();
    });
}

void TaskSocket::onReadyRead() {
    try {
        parser.readSocket(this);
        if (!parser.hasCompleteRequest()) {
            return;
        }
        auto request = parser.getNextRequest();
        qDebug() << "-------------request------------------";
        qDebug() << request.getEndpoint();
        qDebug() << request.getCredential()->toString();
        qDebug() << request.getData();
        qDebug() << "+++++++++++++request+++++++++++++++++++";
        auto response = rpcController->process(request);
        qDebug() << "-------------response------------------";
        qDebug() << response.success;
        qDebug() << response.message;
        qDebug() << response.data;
        qDebug() << "+++++++++++++response+++++++++++++++++++";

        auto bytes = response.toStream();
        qDebug() << bytes;
        qDebug() << write(bytes);
        flush();
        disconnectFromHost();
    } catch (std::exception& e) {
        try {
            auto response = Response::error("网络错误");
            auto bytes = response.toStream();
            write(bytes);
        } catch (...) {
        }
        close();
    }
}
