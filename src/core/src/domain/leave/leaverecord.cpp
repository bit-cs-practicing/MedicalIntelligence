#include "leaverecord.h"

LeaveRecord::LeaveRecord(Id leaveId, Id doctorId, LeavePeriod leavePeriod)
    : leaveId(leaveId), doctorId(doctorId), leavePeriod(leavePeriod), leaveStatus(LeaveStatus::ACTIVE) {}

const Id& LeaveRecord::getLeaveId() const {
    return leaveId;
}

const Id& LeaveRecord::getDoctorId() const {
    return doctorId;
}

const LeavePeriod& LeaveRecord::getLeavePeriod() const {
    return leavePeriod;
}

const LeaveStatus& LeaveRecord::getLeaveStatus() const {
    return leaveStatus;
}

void LeaveRecord::cancelLeave() {
    if (leaveStatus.getValue() == LeaveStatus::ACTIVE) {
        leaveStatus = LeaveStatus(LeaveStatus::CANCELED);
    } else {
        throw std::logic_error("请假记录状态不允许销假或已销假");
    }
}
