#include "rpcclient.h"

#include <QJsonDocument>
#include <QThread>

Response RpcClient::rpc(Request request) {
    QTcpSocket client;
    client.connectToHost(serverIp, serverPort);
    if (!client.waitForConnected(5000)) {
        return Response::error("连接错误");
    }
    client.write(request.toStream());
    ResponseParser parser;
    for (int retry = 0; retry < 5; retry++) {
        if (client.waitForReadyRead(2000) && client.isOpen()) {
            auto response = onReadyRead(&client, &parser);
            if (response.has_value()) {
                return response.value();
            }
        }
    }
    return Response::error("请求次数上限");
}

std::optional<Response> RpcClient::onReadyRead(QTcpSocket *socket, ResponseParser *parser) {
    try {
        parser->readSocket(socket);
        if (!parser->hasCompleteResponse()) {
            return std::nullopt;
        }
        return parser->getNextResponse();
    } catch (std::exception& e) {
        return Response::error("网络错误");
    }
}
