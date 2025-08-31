#ifndef RPCCONTROLLER_H
#define RPCCONTROLLER_H

#include "infra/protocol/request.h"
#include "infra/protocol/response.h"

class RpcController {
public:
    virtual ~RpcController() = default;

    Response process(const Request& request);
protected:
    virtual Response processImpl(const Request& request) = 0;
};

#endif // RPCCONTROLLER_H
