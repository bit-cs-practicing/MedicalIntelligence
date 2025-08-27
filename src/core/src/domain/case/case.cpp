#include "case.h"

Case::Case(
    Id caseId,
    Id appointmentId,
    CaseDiagnosis diagnosis,
    CasePrescription prescription,
    CaseAdvice advice,
    QDate visitDate
)
    : caseId(caseId)
    , appointmentId(appointmentId)
    , diagnosis(diagnosis)
    , prescription(prescription)
    , advice(advice)
    , visitDate(visitDate)
{
}

const Id& Case::getCaseId() const {
    return caseId;
}

const Id& Case::getAppointmentId() const {
    return appointmentId;
}

const CaseDiagnosis& Case::getDiagnosis() const {
    return diagnosis;
}

const CasePrescription& Case::getPrescription() const {
    return prescription;
}

const CaseAdvice& Case::getAdvice() const {
    return advice;
}

const QDate& Case::getVisitDate() const {
    return visitDate;
}

void Case::setDiagnosis(const CaseDiagnosis& diagnosis) {
    this->diagnosis = diagnosis;
}

void Case::setPrescription(const CasePrescription& prescription) {
    this->prescription = prescription;
}

void Case::setAdvice(const CaseAdvice& advice) {
    this->advice = advice;
}
