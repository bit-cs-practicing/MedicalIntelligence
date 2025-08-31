#include "appointmenttimeslot.h"

#include <stdexcept>

#include <QRegExp>

AppointmentTimeSlot::AppointmentTimeSlot(const QTime& startTime, const QTime& endTime)
    : startTime(startTime), endTime(endTime) {
    if (!startTime.isValid() || !endTime.isValid()) {
        throw std::invalid_argument("无效的时间");
    }
    if (startTime >= endTime) {
        throw std::invalid_argument("开始时间不能晚于结束时间");
    }
}

const QTime& AppointmentTimeSlot::getStartTime() const {
    return startTime;
}

const QTime& AppointmentTimeSlot::getEndTime() const {
    return endTime;
}

QString AppointmentTimeSlot::toString() const {
    return startTime.toString("hh:mm") + "-" + endTime.toString("hh:mm");
}

AppointmentTimeSlot AppointmentTimeSlot::parse(const QString& timeSlotStr) {
    QRegExp regExp("^([0-9]{2}:[0-9]{2})-([0-9]{2}:[0-9]{2})$");
    if (!regExp.exactMatch(timeSlotStr)) {
        throw std::invalid_argument("时间段格式不正确，正确格式应为 HH:mm-HH:mm");
    }
    QString startStr = regExp.cap(1);
    QString endStr = regExp.cap(2);
    QTime startTime = QTime::fromString(startStr, "hh:mm");
    QTime endTime = QTime::fromString(endStr, "hh:mm");
    if (!startTime.isValid() || !endTime.isValid()) {
        throw std::invalid_argument("时间段字符串包含无效时间");
    }
    return AppointmentTimeSlot(startTime, endTime);
}
