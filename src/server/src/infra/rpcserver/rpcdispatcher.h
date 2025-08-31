#ifndef RPCDISPATCHER_H
#define RPCDISPATCHER_H

#include <memory>

#include <QMap>

#include "infra/protocol/request.h"
#include "infra/protocol/response.h"

#include "rpccontroller.h"

class RpcDispatcher : public RpcController {
public:
    RpcDispatcher();

    void add(QString endpoint, std::shared_ptr<RpcController> controller);
protected:
    virtual Response processImpl(const Request& request) override;
private:
    QMap<QString, std::shared_ptr<RpcController>> controllers;

};

#endif // RPCDISPATCHER_H
