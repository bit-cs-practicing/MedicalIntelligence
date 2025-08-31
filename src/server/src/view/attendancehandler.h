#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <memory>

#include "app/attendance/attendanceappservice.h"
#include "infra/rpcserver/rpchandler.h"

class AttendanceCheckInHandler : public RpcAuthHandler {
public:
    AttendanceCheckInHandler(std::shared_ptr<AttendanceAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->checkIn(credential, data));
    }
private:
    std::shared_ptr<AttendanceAppService> service;
};

class AttendanceLeaveRequestHandler : public RpcAuthHandler {
public:
    AttendanceLeaveRequestHandler(std::shared_ptr<AttendanceAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->leaveRequest(credential, data));
    }
private:
    std::shared_ptr<AttendanceAppService> service;
};

class AttendanceLeaveCancelHandler : public RpcAuthHandler {
public:
    AttendanceLeaveCancelHandler(std::shared_ptr<AttendanceAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->leaveCancel(credential, data));
    }
private:
    std::shared_ptr<AttendanceAppService> service;
};

class AttendanceFetchLastRequestHandler : public RpcAuthHandler {
public:
    AttendanceFetchLastRequestHandler(std::shared_ptr<AttendanceAppService> service): service(service) {};
protected:
    virtual Response handle(const Credential &credential, const QJsonObject &data) override {
        return Response::ok(service->fetchLastRequest(credential, data));
    }
private:
    std::shared_ptr<AttendanceAppService> service;
};

#endif // ATTENDANCE_H
