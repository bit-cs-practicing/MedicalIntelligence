#ifndef CASEHANDLER_H
#define CASEHANDLER_H

#include <memory>

#include "app/case/caseappservice.h"
#include "infra/rpcserver/rpchandler.h"

class CaseCreateHandler : public RpcAuthHandler {
public:
    CaseCreateHandler(std::shared_ptr<CaseAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->create(credential, data));
    }
private:
    std::shared_ptr<CaseAppService> service;
};

class CaseUpdateHandler : public RpcAuthHandler {
public:
    CaseUpdateHandler(std::shared_ptr<CaseAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->update(credential, data));
    }
private:
    std::shared_ptr<CaseAppService> service;
};

class CaseListByPatientHandler : public RpcAuthHandler {
public:
    CaseListByPatientHandler(std::shared_ptr<CaseAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->listByPatient(credential, data));
    }
private:
    std::shared_ptr<CaseAppService> service;
};

class CaseListByDoctorAndPatientHandler : public RpcAuthHandler {
public:
    CaseListByDoctorAndPatientHandler(std::shared_ptr<CaseAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject &data) override {
        return Response::ok(service->listByDoctorAndPatient(credential, data));
    }
private:
    std::shared_ptr<CaseAppService> service;
};

#endif // CASEHANDLER_H
