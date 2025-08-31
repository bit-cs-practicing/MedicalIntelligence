#include "rpcserver.h"

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
    connect(task, &QAbstractSocket::disconnected, this, &QObject::deleteLater);
}

TaskSocket::TaskSocket(qintptr socketDescriptor, RpcController* rpcController):
    rpcController(rpcController)
{
    setSocketDescriptor(socketDescriptor);
    connect(this, &QAbstractSocket::readyRead, this, &TaskSocket::onReadyRead);
    connect(this, &QAbstractSocket::disconnected, this, &QObject::deleteLater);
}

void TaskSocket::onReadyRead() {
    try {
        parser.readSocket(this);
        if (!parser.hasCompleteRequest()) {
            return;
        }
        auto request = parser.getNextRequest();
        auto response = rpcController->process(request);
        auto bytes = response.toStream();
        write(bytes);
        close();
    } catch (std::exception e) {
        try {
            auto response = Response::error("网络错误");
            auto bytes = response.toStream();
            write(bytes);
        } catch (...) {
        }
        close();
    }
}
