#include "rpchandler.h"

Response RpcHandler::processImpl(const Request& request) {
    return handle(request.data);
}

Response RpcAuthHandler::processImpl(const Request& request) {
    auto credential = Credential::parse(request.credential);
    return handle(credential, request.data);
}
