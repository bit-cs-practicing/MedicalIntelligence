#ifndef RPCSERVER_H
#define RPCSERVER_H

#include <QThreadPool>
#include <QRunnable>
#include <QTcpServer>
#include <QTcpSocket>

#include "infra/protocol/requestparser.h"

#include "rpccontroller.h"

class RpcServer : public QTcpServer {
    Q_OBJECT
public:
    RpcServer(std::unique_ptr<RpcController> rpcController, QObject* parent = nullptr);
protected:
    virtual void incomingConnection(qintptr handle) override;
private:
    QThreadPool executor;
    std::unique_ptr<RpcController> rpcController;
};

class Carrier : public QObject, public QRunnable{
public:
    Carrier(qintptr socketDescriptor, RpcController* rpcController);

    virtual void run() override;
private:
    qintptr socketDescriptor;
    RpcController* rpcController;
};

class TaskSocket : public QTcpSocket {
    Q_OBJECT
public:
    TaskSocket(qintptr socketDescriptor, RpcController* rpcController);
private:
    RequestParser parser;
    RpcController* rpcController;
public slots:
    void onReadyRead();
};

#endif // RPCSERVER_H
