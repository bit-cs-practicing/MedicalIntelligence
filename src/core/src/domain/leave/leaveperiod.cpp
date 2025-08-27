#include "leaveperiod.h"

#include <stdexcept>

LeavePeriod::LeavePeriod(const QDateTime& startTime, const QDateTime& endTime) {
    if (startTime >= endTime) {
        throw std::invalid_argument("请假结束时间不能早于或等于开始时间");
    }
    this->startTime = startTime;
    this->endTime = endTime;
}

const QDateTime& LeavePeriod::getStartTime() const {
    return startTime;
}

const QDateTime& LeavePeriod::getEndTime() const {
    return endTime;
}
