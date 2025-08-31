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
    setAutoDelete(false);
}

void Carrier::run() {
    auto task = new TaskSocket(socketDescriptor, rpcController);
    qDebug() << QString("%1:%2").arg(task->peerAddress().toString()).arg(task->peerPort());
    int cnt = 0;
    while (task->isOpen() && cnt < 500) {
        qDebug() << "waiting..." << ++cnt;
        if (task->waitForReadyRead(2000)) {
            qDebug() << "ready for read";
            task->onReadyRead();
        }
    }
//    connect(task, &QAbstractSocket::disconnected, this, &QObject::deleteLater);
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
        write(bytes);
        close();
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
