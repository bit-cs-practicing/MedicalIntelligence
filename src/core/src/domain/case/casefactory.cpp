#include "casefactory.h"

#include <stdexcept>

CaseFactory::CaseFactory() {

}

Case CaseFactory::createCase(
    const Doctor& doctor,
    const Appointment& appointment,
    CaseDiagnosis diagnosis,
    CasePrescription prescription,
    CaseAdvice advice
) const {
    if (appointment.getDoctorId().getId() != doctor.getId().getId()) {
        throw std::logic_error("无权限创建病例");
    }
    Id id = Id::fromUuid();
    Id appointmentId = appointment.getAppointmentId();
    QDate visitDate = QDate::currentDate();
    return Case(id, appointmentId, diagnosis, prescription, advice, visitDate);
}
