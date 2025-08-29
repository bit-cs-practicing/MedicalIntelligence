#include "attendancefactory.h"

#include <QDate>

AttendanceFactory::AttendanceFactory(std::shared_ptr<AttendanceRepository> attendanceRepository)
    : attendanceRepository(attendanceRepository)
{
}

Attendance AttendanceFactory::createAttendance(const Doctor& doctor) const {
    auto currentDate = QDate::currentDate();
    auto currentTime = QTime::currentTime();
    checkTimeInSchedule(currentTime, doctor);
    checkNoAttendanceToday(currentDate, doctor);
    return Attendance(Id::fromUuid(), doctor.getId(), QDateTime(currentDate, currentTime));
}

void AttendanceFactory::checkTimeInSchedule(const QTime& currentTime, const Doctor& doctor) const {
    if (!doctor.getWorkSchedule().has_value()) {
        return;
    }
    auto schedule = doctor.getWorkSchedule().value();
    auto start = schedule.getStartTime();
    auto end = schedule.getEndTime();
    if (currentTime < start || end < currentTime) {
        throw std::logic_error("无法在非上班时间打卡");
    }
}

void AttendanceFactory::checkNoAttendanceToday(const QDate& currentDate, const Doctor& doctor) const {
    auto lastAttendanceOpt = attendanceRepository->getLastByDoctorIdOrderedByTime(doctor.getId());
    if (!lastAttendanceOpt.has_value()) {
        return;
    }
    auto lastAttendance = lastAttendanceOpt.value();
    if (lastAttendance.getAttendanceTime().date() == currentDate) {
        throw std::logic_error("今日已打卡，无法重复打卡");
    }
}
