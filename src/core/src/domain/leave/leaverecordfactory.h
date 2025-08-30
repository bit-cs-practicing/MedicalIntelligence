#ifndef LEAVEFACTORY_H
#define LEAVEFACTORY_H

#include <memory>

#include "../doctor/doctor.h"
#include "leaverecord.h"
#include "leaverecordrepository.h"

class LeaveRecordFactory {
public:
    LeaveRecordFactory(std::shared_ptr<LeaveRecordRepository> leaveRecordRepository);

    LeaveRecord createLeaveRecord(const Doctor& doctor, QDateTime start, QDateTime end) const;
private:
    std::shared_ptr<LeaveRecordRepository> leaveRecordRepository;

    void checkLastLeaveCancelled(const Doctor& doctor) const;
};

#endif // LEAVEFACTORY_H
