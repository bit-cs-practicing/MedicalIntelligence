#include "attendanceappserviceimpl.h"

#include <stdexcept>

AttendanceAppServiceImpl::AttendanceAppServiceImpl(
    std::shared_ptr<AttendanceRepository> attendanceRepository,
    std::shared_ptr<AttendanceFactory> attendanceFactory,
    std::shared_ptr<LeaveRecordRepository> leaveRecordRepository,
    std::shared_ptr<LeaveRecordFactory> leaveRecordFactory,
    std::shared_ptr<LeaveRecordService> leaveRecordService,
    std::shared_ptr<DoctorRepository> doctorRepository,
    std::shared_ptr<CredentialRegistry> credentialRegistry
)
    : attendanceRepository(std::move(attendanceRepository))
    , attendanceFactory(std::move(attendanceFactory))
    , leaveRecordRepository(std::move(leaveRecordRepository))
    , leaveRecordFactory(std::move(leaveRecordFactory))
    , leaveRecordService(std::move(leaveRecordService))
    , doctorRepository(std::move(doctorRepository))
    , credentialRegistry(std::move(credentialRegistry))
{
}

QJsonObject AttendanceAppServiceImpl::checkIn(const Credential& credential, const QJsonObject&) {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }
    auto doctor = doctorOpt.value();

    auto attendance = attendanceFactory->createAttendance(doctor);
    attendanceRepository->save(attendance);

    return QJsonObject {
        { "attendanceId", attendance.getAttendanceId().getId() },
        { "time", attendance.getAttendanceTime().toString("yyyy-MM-ddTHH:mm:ss") }
    };
}

QJsonObject AttendanceAppServiceImpl::leaveRequest(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }
    auto doctor = doctorOpt.value();

    auto startTime = QDateTime::fromString(data["startTime"].toString(), "yyyy-MM-ddTHH:mm:ss");
    auto endTime = QDateTime::fromString(data["endTime"].toString(), "yyyy-MM-ddTHH:mm:ss");

    auto leaveRecord = leaveRecordFactory->createLeaveRecord(doctor, startTime, endTime);
    leaveRecordRepository->save(leaveRecord);

    auto period = leaveRecord.getLeavePeriod();
    return QJsonObject {
        { "startTime", period.getStartTime().toString("yyyy-MM-ddTHH:mm:ss") },
        { "endTime", period.getEndTime().toString("yyyy-MM-ddTHH:mm:ss") }
    };
}

QJsonObject AttendanceAppServiceImpl::leaveCancel(const Credential &credential, const QJsonObject &data) {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }
    auto doctor = doctorOpt.value();

    auto leaveRecordId = Id(data["leaveId"].toString());
    auto leaveRecordOpt = leaveRecordRepository->getById(leaveRecordId);
    if (!leaveRecordOpt.has_value()) {
        throw std::logic_error("不存在此请假记录");
    }
    auto leaveRecord = leaveRecordOpt.value();

    leaveRecordService->cancelLeave(&leaveRecord, doctor);
    leaveRecordRepository->save(leaveRecord);

    return QJsonObject {};
}

QJsonObject AttendanceAppServiceImpl::fetchLastRequest(const Credential &credential, const QJsonObject &) const {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    if (!doctorRepository->getById(doctorId).has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }

    auto leaveRecordOpt = leaveRecordRepository->getLastByDoctorId(doctorId);
    if (!leaveRecordOpt.has_value()) {
        throw std::logic_error("不存在请假记录");
    }
    auto leaveRecord = leaveRecordOpt.value();

    auto period = leaveRecord.getLeavePeriod();
    return QJsonObject {
        { "leaveId", leaveRecord.getLeaveId().getId() },
        { "startTime", period.getStartTime().toString("yyyy-MM-ddTHH:mm:ss") },
        { "endTime", period.getEndTime().toString("yyyy-MM-ddTHH:mm:ss") }
    };
}

