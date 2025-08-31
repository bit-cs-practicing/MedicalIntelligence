#include "rpccontroller.h"

Response RpcController::process(const Request &request) {
    try {
        processImpl(request);
    } catch (std::exception e) {
        return Response::error(e.what());
    } catch (...) {
        return Response::error("服务器内部错误");
    }
}
