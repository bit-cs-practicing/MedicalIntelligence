#ifndef LEAVERECORDSERVICE_H
#define LEAVERECORDSERVICE_H

#include "domain/doctor/doctor.h"

#include "leaverecord.h"

class LeaveRecordService {
public:
    LeaveRecordService();

    void cancelLeave(LeaveRecord* leaveRecord, const Doctor& doctor) const;
};

#endif // LEAVERECORDSERVICE_H
