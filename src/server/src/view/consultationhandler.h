#ifndef CONSULTATIONHANDLER_H
#define CONSULTATIONHANDLER_H

#include <memory>

#include "app/consultation/consultationappservice.h"
#include "infra/rpcserver/rpchandler.h"

class ConsultationAnswerForDoctorHandler : public RpcAuthHandler {
public:
    ConsultationAnswerForDoctorHandler(std::shared_ptr<ConsultationAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject& data) override {
        return Response::ok(service->answerForDoctor(credential, data));
    }
private:
    std::shared_ptr<ConsultationAppService> service;
};

class ConsultationAnswerForPatientHandler : public RpcAuthHandler {
public:
    ConsultationAnswerForPatientHandler(std::shared_ptr<ConsultationAppService> service): service(service) {}
protected:
    virtual Response handle(const Credential& credential, const QJsonObject& data) override {
        return Response::ok(service->answerForPatient(credential, data));
    }
private:
    std::shared_ptr<ConsultationAppService> service;
};

#endif // CONSULTATIONHANDLER_H
