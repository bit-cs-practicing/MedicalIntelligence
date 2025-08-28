#ifndef LEAVERECORDREPOSITORY_H
#define LEAVERECORDREPOSITORY_H

#include "leaverecord.h"
#include <optional>

class LeaveRecordRepository {
public:
    virtual ~LeaveRecordRepository() = 0;

    virtual void save(const LeaveRecord& leaveRecord) = 0;
    virtual std::optional<LeaveRecord> getById(const Id& leaveId) = 0;
    virtual std::optional<LeaveRecord> getLastByDoctorId(const Id& doctorId) = 0;
};

#endif // LEAVERECORDREPOSITORY_H
