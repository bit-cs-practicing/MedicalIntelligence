#include "workschedule.h"

#include <stdexcept>

WorkSchedule::WorkSchedule(QString workSchedule): workSchedule(workSchedule) {
    if (this->workSchedule.isEmpty()) {
        throw std::logic_error("上班时间不可以为空");
    }
}

const QString& WorkSchedule::getValue() const {
    return this->workSchedule;
}
