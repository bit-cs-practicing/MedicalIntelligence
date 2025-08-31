#include "rpchandler.h"

Response RpcHandler::processImpl(const Request& request) {
    return handle(request.getData());
}

Response RpcAuthHandler::processImpl(const Request& request) {
    auto credentialOpt = request.getCredential();
    if (credentialOpt.has_value()) {
        return handle(credentialOpt.value(), request.getData());
    } else {
        throw std::invalid_argument("未认证");
    }
}
