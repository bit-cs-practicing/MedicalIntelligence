#ifndef PATIENTHANDLER_H
#define PATIENTHANDLER_H

#include <memory>

#include "app/patient/patientappservice.h"
#include "infra/rpcserver/rpchandler.h"

class PatientRegisterHandler : public RpcHandler {
public:
    PatientRegisterHandler(std::shared_ptr<PatientAppService> service): service(service) {};
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->signup(data));
    }
private:
    std::shared_ptr<PatientAppService> service;
};

class PatientLoginHandler : public RpcHandler {
public:
    PatientLoginHandler(std::shared_ptr<PatientAppService> service): service(service) {};
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->login(data));
    }
private:
    std::shared_ptr<PatientAppService> service;
};

class PatientUpdateInfoHandler : public RpcAuthHandler {
public:
    PatientUpdateInfoHandler(std::shared_ptr<PatientAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->updateInfo(credential, data));
    }
private:
    std::shared_ptr<PatientAppService> service;
};

class PatientFetchInfoHandler : public RpcHandler {
public:
    PatientFetchInfoHandler(std::shared_ptr<PatientAppService> service): service(service) {};
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->fetchInfo(data));
    }
private:
    std::shared_ptr<PatientAppService> service;
};

class PatientFetchInfoByNameHandler : public RpcHandler {
public:
    PatientFetchInfoByNameHandler(std::shared_ptr<PatientAppService> service): service(service) {};
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->fetchInfoByName(data));
    }
private:
    std::shared_ptr<PatientAppService> service;
};

class PatientFetchInfoByIdCardHandler : public RpcHandler {
public:
    PatientFetchInfoByIdCardHandler(std::shared_ptr<PatientAppService> service): service(service) {};
protected:
    virtual Response handle(const QJsonObject &data) override {
        return Response::ok(service->fetchInfoByIdCard(data));
    }
private:
    std::shared_ptr<PatientAppService> service;
};

class PatientUpdatePasswordHandler : public RpcAuthHandler {
public:
    PatientUpdatePasswordHandler(std::shared_ptr<PatientAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->updatePassword(credential, data));
    }
private:
    std::shared_ptr<PatientAppService> service;
};

#endif // PATIENTHANDLER_H
