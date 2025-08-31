#ifndef CHATHANDLER_H
#define CHATHANDLER_H

#include <memory>

#include "app/chat/chatappservice.h"
#include "infra/rpcserver/rpchandler.h"

class ChatCreateTopicHandler : public RpcAuthHandler {
public:
    ChatCreateTopicHandler(std::shared_ptr<ChatAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->createTopic(credential, data));
    }
private:
    std::shared_ptr<ChatAppService> service;
};

class ChatListTopicsByUserHandler : public RpcAuthHandler {
public:
    ChatListTopicsByUserHandler(std::shared_ptr<ChatAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->listTopicsByUser(credential, data));
    }
private:
    std::shared_ptr<ChatAppService> service;
};

class ChatSendMessageHandler : public RpcAuthHandler {
public:
    ChatSendMessageHandler(std::shared_ptr<ChatAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->sendMessage(credential, data));
    }
private:
    std::shared_ptr<ChatAppService> service;
};

class ChatFetchMessagesHandler : public RpcAuthHandler {
public:
    ChatFetchMessagesHandler(std::shared_ptr<ChatAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->fetchMessages(credential, data));
    }
private:
    std::shared_ptr<ChatAppService> service;
};

#endif // CHATHANDLER_H
