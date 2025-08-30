#include "appointmentservice.h"

#include <cassert>
#include <stdexcept>

AppointmentService::AppointmentService() {

}

void AppointmentService::completeAppointment(Appointment* appointment, const Doctor& doctor) const {
    assert(appointment != nullptr);
    if (appointment->getDoctorId().getId() != doctor.getId().getId()) {
        throw std::logic_error("无法完成不属于自己的预约");
    }
    appointment->markAsCompleted();
}

void AppointmentService::cancelAppointment(Appointment* appointment, const Patient& patient) const {
    assert(appointment != nullptr);
    if (appointment->getPatientId().getId() != patient.getId().getId()) {
        throw std::logic_error("无法取消不属于自己的预约");
    }
    appointment->markAsCancelled();
}
