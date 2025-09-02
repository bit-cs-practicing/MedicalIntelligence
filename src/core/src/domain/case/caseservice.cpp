#include "caseservice.h"

#include <stdexcept>

CaseService::CaseService(std::shared_ptr<AppointmentRepository> appointmentRepository)
    : appointmentRepository(appointmentRepository)
{
}

void CaseService::updateCase(
    Case* caze,
    const Doctor& doctor,
    std::optional<CaseDiagnosis> diagnosis,
    std::optional<CasePrescription> prescription,
    std::optional<CaseAdvice> advice
) const {
    auto appointmentOpt = appointmentRepository->getById(caze->getAppointmentId());
    if (!appointmentOpt.has_value()) {
        throw std::runtime_error("无法找到病例对应的预约");
    }
    auto appointment = appointmentOpt.value();
    if (appointment.getDoctorId().getId() != doctor.getId().getId()) {
        throw std::logic_error("无权限修改病例");
    }
    if (diagnosis.has_value()) {
        caze->setDiagnosis(diagnosis.value());
    }
    if (prescription.has_value()) {
        caze->setPrescription(prescription.value());
    }
    if (advice.has_value()) {
        caze->setAdvice(advice.value());
    }
}
