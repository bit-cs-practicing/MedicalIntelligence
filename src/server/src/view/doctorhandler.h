#ifndef DOCTORHANDLER_H
#define DOCTORHANDLER_H

#include <memory>

#include "app/doctor/doctorappservice.h"
#include "infra/rpcserver/rpchandler.h"

class DoctorRegisterHandler : public RpcHandler {
public:
    DoctorRegisterHandler(std::shared_ptr<DoctorAppService> service): service(service) {}
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->signup(data));
    }
private:
    std::shared_ptr<DoctorAppService> service;
};

class DoctorLoginHandler : public RpcHandler {
public:
    DoctorLoginHandler(std::shared_ptr<DoctorAppService> service): service(service) {}
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->login(data));
    }
private:
    std::shared_ptr<DoctorAppService> service;
};

class DoctorUpdateInfoHandler : public RpcAuthHandler {
public:
    DoctorUpdateInfoHandler(std::shared_ptr<DoctorAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->updateInfo(credential, data));
    }
private:
    std::shared_ptr<DoctorAppService> service;
};

class DoctorFetchInfoHandler : public RpcHandler {
public:
    DoctorFetchInfoHandler(std::shared_ptr<DoctorAppService> service): service(service) {}
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->fetchInfo(data));
    }
private:
    std::shared_ptr<DoctorAppService> service;
};

class DoctorFetchAllInfoHandler : public RpcHandler {
public:
    DoctorFetchAllInfoHandler(std::shared_ptr<DoctorAppService> service): service(service) {}
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->fetchAllInfo(data));
    }
private:
    std::shared_ptr<DoctorAppService> service;
};

class DoctorUpdatePasswordHandler : public RpcAuthHandler {
public:
    DoctorUpdatePasswordHandler(std::shared_ptr<DoctorAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->updatePassword(credential, data));
    }
private:
    std::shared_ptr<DoctorAppService> service;
};

#endif // DOCTORHANDLER_H
