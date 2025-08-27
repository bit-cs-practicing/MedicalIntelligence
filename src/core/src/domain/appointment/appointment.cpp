#include "appointment.h"

#include <stdexcept>

Appointment::Appointment(
    Id appointmentId,
    Id doctorId,
    Id patientId,
    QDate date,
    AppointmentTimeSlot timeSlot
)
    : appointmentId(appointmentId)
    , doctorId(doctorId)
    , patientId(patientId)
    , date(date)
    , timeSlot(timeSlot)
    , status(AppointmentStatus(AppointmentStatus::SCHEDULED))
{
}

const Id& Appointment::getAppointmentId() const {
    return appointmentId;
}

const Id& Appointment::getDoctorId() const {
    return doctorId;
}

const Id& Appointment::getPatientId() const {
    return patientId;
}

const QDate& Appointment::getDate() const {
    return date;
}

const AppointmentTimeSlot& Appointment::getTimeSlot() const {
    return timeSlot;
}

const AppointmentStatus& Appointment::getStatus() const {
    return status;
}

void Appointment::markAsCompleted() {
    if (status.getValue() != AppointmentStatus::SCHEDULED) {
        throw std::logic_error("预约无法再次标记为完成");
    }
    status = AppointmentStatus(AppointmentStatus::COMPLETED);
}

void Appointment::markAsCancelled() {
    if (status.getValue() != AppointmentStatus::SCHEDULED) {
        throw std::logic_error("预约无法再次标记为取消");
    }
    status = AppointmentStatus(AppointmentStatus::CANCELLED);
}
