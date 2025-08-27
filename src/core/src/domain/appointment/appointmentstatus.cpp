#include "appointmentstatus.h"

#include <stdexcept>

const QString AppointmentStatus::SCHEDULED = "scheduled";
const QString AppointmentStatus::COMPLETED = "completed";
const QString AppointmentStatus::CANCELLED = "cancelled";

AppointmentStatus::AppointmentStatus(const QString& status): status(status) {
    if (status != AppointmentStatus::SCHEDULED && status != AppointmentStatus::COMPLETED && status != AppointmentStatus::CANCELLED) {
        throw std::invalid_argument("预约状态无效，必须是 'scheduled'、'completed' 或 'cancelled'");
    }
}

const QString& AppointmentStatus::getValue() const {
    return status;
}
