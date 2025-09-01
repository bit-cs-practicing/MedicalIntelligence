#include "appointmentfactory.h"

#include <stdexcept>

AppointmentFactory::AppointmentFactory(
    std::shared_ptr<AppointmentRepository> appointmentRepository,
    std::shared_ptr<DoctorRepository> doctorRepository,
    std::shared_ptr<LeaveRecordRepository> leaveRecordRepository
)
    : appointmentRepository(std::move(appointmentRepository))
    , doctorRepository(std::move(doctorRepository))
    , leaveRecordRepository(std::move(leaveRecordRepository))
{
}

Appointment AppointmentFactory::createAppointment(
    const Doctor& doctor,
    const Patient& patient,
    QDate date,
    AppointmentTimeSlot timeSlot
) const {
    checkLeaveNotOverlapped(doctor, date, timeSlot);
    auto appointments = appointmentRepository->getAllByDoctorIdAndDate(doctor.getId(), date);
    checkAppointmentNotFull(doctor, appointments);
    checkAppointmentNotOverlapped(appointments, timeSlot);

    auto id = Id::fromUuid();
    return Appointment(id, doctor.getId(), patient.getId(), date, timeSlot);
}

void AppointmentFactory::checkLeaveNotOverlapped(
    const Doctor& doctor,
    const QDate& date,
    const AppointmentTimeSlot& timeSlot
) const {
    auto lastLeaveOpt = leaveRecordRepository->getLastByDoctorId(doctor.getId());
    if (!lastLeaveOpt.has_value()) {
        return;
    }
    auto lastLeave = lastLeaveOpt.value();
    if (lastLeave.getLeaveStatus().getValue() == LeaveStatus::CANCELED) {
        return;
    }
    auto period = lastLeave.getLeavePeriod();
    auto s1 = period.getStartTime();
    auto e1 = period.getEndTime();
    auto s2 = QDateTime(date, timeSlot.getStartTime());
    auto e2 = QDateTime(date, timeSlot.getEndTime());
    if (e1 <= s2 || s1 >= e2) {
        return;
    }
    throw std::logic_error("预约时间与医生请假时间冲突");
}

void AppointmentFactory::checkAppointmentNotFull(
    const Doctor &doctor,
    const QList<Appointment>& appointments
) const {
    if (!doctor.getDailyPatientLimit().has_value()) {
        return;
    }
    auto currentNum = appointments.size();
    if (currentNum >= doctor.getDailyPatientLimit()->getValue()) {
        throw std::logic_error("预约数量已达上限");
    }
}

void AppointmentFactory::checkAppointmentNotOverlapped(
    const QList<Appointment>& appointments,
    const AppointmentTimeSlot& timeSlot
) const {
    auto s1 = timeSlot.getStartTime(), e1 = timeSlot.getEndTime();
    for (auto& appointment : appointments) {
        if (appointment.getStatus().getValue() == AppointmentStatus::CANCELLED) {
            continue;
        }
        auto s2 = appointment.getTimeSlot().getStartTime();
        auto e2 = appointment.getTimeSlot().getEndTime();
        if (!(e1 <= s2 || s1 >= e2)) {
            throw std::logic_error("时间段与现有预约冲突");
        }
    }
}
