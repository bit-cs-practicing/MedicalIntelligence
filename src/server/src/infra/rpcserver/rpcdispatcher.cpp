#include "rpcdispatcher.h"

RpcDispatcher::RpcDispatcher() {

}

void RpcDispatcher::add(QString endpoint, std::unique_ptr<RpcController> controller) {
    controllers.insert(endpoint, std::move(controller));
}

Response RpcDispatcher::processImpl(const Request& request) {
    auto endpoint = request.endpoint;
    auto controller = controllers.find(endpoint);
    if (controller == controllers.end()) {
        return Response::error("不合法的 API endpoint: " + endpoint);
    }
    return controller.value()->process(request);
}
