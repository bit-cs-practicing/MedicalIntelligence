#ifndef ATTENDANCEAPPSERVICEIMPL_H
#define ATTENDANCEAPPSERVICEIMPL_H

#include <memory>

#include "../../domain/attendance/attendance.h"
#include "../../domain/attendance/attendancerepository.h"
#include "../../domain/attendance/attendancefactory.h"
#include "../../domain/leave/leaverecordrepository.h"
#include "../../domain/leave/leaverecordfactory.h"
#include "../../domain/leave/leaverecordservice.h"
#include "../../domain/doctor/doctorrepository.h"
#include "../../infra/security/credentialregistry.h"
#include "attendanceappservice.h"

class AttendanceAppServiceImpl : public AttendanceAppService {
public:
    AttendanceAppServiceImpl(
        std::shared_ptr<AttendanceRepository> attendanceRepository,
        std::shared_ptr<AttendanceFactory> attendanceFactory,
        std::shared_ptr<LeaveRecordRepository> leaveRecordRepository,
        std::shared_ptr<LeaveRecordFactory> leaveRecordFactory,
        std::shared_ptr<LeaveRecordService> leaveRecordService,
        std::shared_ptr<DoctorRepository> doctorRepository,
        std::shared_ptr<CredentialRegistry> credentialRegistry
    );

    virtual QJsonObject checkIn(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject leaveRequest(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject leaveCancel(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject fetchLastRequest(const Credential& credential, const QJsonObject& data) const override;
private:
    std::shared_ptr<AttendanceRepository> attendanceRepository;
    std::shared_ptr<AttendanceFactory> attendanceFactory;
    std::shared_ptr<LeaveRecordRepository> leaveRecordRepository;
    std::shared_ptr<LeaveRecordFactory> leaveRecordFactory;
    std::shared_ptr<LeaveRecordService> leaveRecordService;
    std::shared_ptr<DoctorRepository> doctorRepository;
    std::shared_ptr<CredentialRegistry> credentialRegistry;
};

#endif // ATTENDANCEAPPSERVICEIMPL_H
