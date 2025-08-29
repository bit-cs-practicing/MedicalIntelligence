#include "leavefactory.h"

#include <stdexcept>

LeaveFactory::LeaveFactory(std::shared_ptr<LeaveRecordRepository> leaveRecordRepository)
    : leaveRecordRepository(leaveRecordRepository)
{
}

LeaveRecord LeaveFactory::createLeaveRecord(const Doctor& doctor, QDateTime start, QDateTime end) const {
    auto leavePeriod = LeavePeriod(start, end);
    checkLastLeaveCancelled(doctor);
    return LeaveRecord(Id::fromUuid(), doctor.getId(), leavePeriod);
}

void LeaveFactory::checkLastLeaveCancelled(const Doctor& doctor) const {
    auto lastLeaveOpt = leaveRecordRepository->getLastByDoctorId(doctor.getId());
    if (!lastLeaveOpt.has_value()) {
        return;
    }
    auto lastLeave = lastLeaveOpt.value();
    if (lastLeave.getLeaveStatus().getValue() == LeaveStatus::ACTIVE) {
        throw std::logic_error("当前还存在未销的请假");
    }
}


