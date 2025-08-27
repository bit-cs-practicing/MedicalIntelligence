#include "appointmentstatus.h"

#include <stdexcept>

AppointmentStatus::AppointmentStatus(const QString& status): status(status) {
    if (status != "scheduled" && status != "completed" && status != "cancelled") {
        throw std::logic_error("预约状态无效，必须是 'scheduled'、'completed' 或 'cancelled'");
    }
}

const QString& AppointmentStatus::getValue() const {
    return status;
}
