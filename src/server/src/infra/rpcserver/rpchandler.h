#ifndef RPCHANDLER_H
#define RPCHANDLER_H

#include <QJsonObject>

#include "infra/protocol/request.h"
#include "infra/protocol/response.h"
#include "infra/security/credential.h"

#include "rpccontroller.h"

class RpcHandler : public RpcController {
public:
    virtual ~RpcHandler() = default;
protected:
    virtual Response processImpl(const Request& request) override;
    virtual Response handle(const QJsonObject& data) = 0;
};

class RpcAuthHandler : public RpcController {
public:
    virtual ~RpcAuthHandler() = default;
protected:
    virtual Response processImpl(const Request& request) override;
    virtual Response handle(const Credential& credential, const QJsonObject& data) = 0;
};

#endif // RPCHANDLER_H
