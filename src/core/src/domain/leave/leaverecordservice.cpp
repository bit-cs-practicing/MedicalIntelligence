#include "leaverecordservice.h"

#include <cassert>
#include <stdexcept>

LeaveRecordService::LeaveRecordService() {

}

void LeaveRecordService::cancelLeave(LeaveRecord* leaveRecord, const Doctor& doctor) const {
    assert(leaveRecord != nullptr);
    if (leaveRecord->getDoctorId().getId() != doctor.getId().getId()) {
        throw std::logic_error("不允许销除不属于自己的请假");
    }
    leaveRecord->cancelLeave();
}
