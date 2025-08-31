#ifndef APPOINTMENTHANDLER_H
#define APPOINTMENTHANDLER_H

#include <memory>

#include "app/appointment/appointmentappservice.h"
#include "infra/rpcserver/rpchandler.h"

class AppointmentCreateHandler : public RpcAuthHandler {
public:
    AppointmentCreateHandler(std::shared_ptr<AppointmentAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->create(credential, data));
    }
private:
    std::shared_ptr<AppointmentAppService> service;
};

class AppointmentCancelHandler : public RpcAuthHandler {
public:
    AppointmentCancelHandler(std::shared_ptr<AppointmentAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->cancel(credential, data));
    }
private:
    std::shared_ptr<AppointmentAppService> service;
};

class AppointmentCompleteHandler : public RpcAuthHandler {
public:
    AppointmentCompleteHandler(std::shared_ptr<AppointmentAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->complete(credential, data));
    }
private:
    std::shared_ptr<AppointmentAppService> service;
};

class AppointmentListByPatientHandler : public RpcAuthHandler {
public:
    AppointmentListByPatientHandler(std::shared_ptr<AppointmentAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->listByPatient(credential, data));
    }
private:
    std::shared_ptr<AppointmentAppService> service;
};

class AppointmentListByDoctorHandler : public RpcAuthHandler {
public:
    AppointmentListByDoctorHandler(std::shared_ptr<AppointmentAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->listByDoctor(credential, data));
    }
private:
    std::shared_ptr<AppointmentAppService> service;
};

#endif // APPOINTMENTHANDLER_H
