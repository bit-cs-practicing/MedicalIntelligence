#ifndef LEAVERECORD_H
#define LEAVERECORD_H

#include "../id.h"
#include "leaveperiod.h"
#include "leavestatus.h"

class LeaveRecord {
public:
    LeaveRecord(Id leaveId, LeavePeriod leavePeriod);

    const Id& getLeaveId() const;
    const LeavePeriod& getLeavePeriod() const;
    const LeaveStatus& getLeaveStatus() const;
    void cancelLeave();

private:
    Id leaveId;
    LeavePeriod leavePeriod;
    LeaveStatus leaveStatus;
};

#endif // LEAVERECORD_H
