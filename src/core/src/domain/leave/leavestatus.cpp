#include "leavestatus.h"

const QString LeaveStatus::ACTIVE = "active";
const QString LeaveStatus::CANCELED = "canceled";

LeaveStatus::LeaveStatus(const QString& status) : status(status.toLower()) {
    if (this->status != LeaveStatus::ACTIVE && this->status != LeaveStatus::CANCELED) {
        throw std::invalid_argument("无效的请假状态");
    }
}

QString LeaveStatus::getValue() const {
    return status;
}
