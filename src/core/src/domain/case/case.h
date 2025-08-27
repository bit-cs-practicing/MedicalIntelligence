#ifndef CASE_H
#define CASE_H

#include <QDate>

#include "../id.h"
#include "casediagnosis.h"
#include "caseprescription.h"
#include "caseadvice.h"

class Case {
public:
    Case(
        Id caseId,
        Id appointmentId,
        CaseDiagnosis diagnosis,
        CasePrescription prescription,
        CaseAdvice advice,
        QDate visitDate
    );

    const Id& getCaseId() const;
    const Id& getAppointmentId() const;
    const CaseDiagnosis& getDiagnosis() const;
    const CasePrescription& getPrescription() const;
    const CaseAdvice& getAdvice() const;
    const QDate& getVisitDate() const;

    void setDiagnosis(const CaseDiagnosis& diagnosis);
    void setPrescription(const CasePrescription& prescription);
    void setAdvice(const CaseAdvice& advice);

private:
    Id caseId;
    Id appointmentId;
    CaseDiagnosis diagnosis;
    CasePrescription prescription;
    CaseAdvice advice;
    QDate visitDate;
};

#endif // CASE_H
