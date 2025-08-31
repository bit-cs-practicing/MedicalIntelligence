#include "workschedule.h"

#include <stdexcept>

#include <QRegularExpression>

WorkSchedule::WorkSchedule(QTime startTime, QTime endTime)
    : startTime(startTime), endTime(endTime) {}

QString WorkSchedule::toString() const {
    return QString("%1-%2").arg(startTime.toString("hh:mm")).arg(endTime.toString("hh:mm"));
}

WorkSchedule WorkSchedule::fromString(const QString& str) {
    QRegularExpression regex(R"((\d{2}):(\d{2})-(\d{2}):(\d{2}))");
    QRegularExpressionMatch match = regex.match(str);
    if (!match.hasMatch()) {
        throw std::invalid_argument("格式必须为 hh:mm-hh:mm");
    }

    int startHour = match.captured(1).toInt();
    int startMinute = match.captured(2).toInt();
    int endHour = match.captured(3).toInt();
    int endMinute = match.captured(4).toInt();
    QTime startTime(startHour, startMinute);
    QTime endTime(endHour, endMinute);
    return WorkSchedule(startTime, endTime);
}

QTime WorkSchedule::getStartTime() const {
    return startTime;
}

QTime WorkSchedule::getEndTime() const {
    return endTime;
}
