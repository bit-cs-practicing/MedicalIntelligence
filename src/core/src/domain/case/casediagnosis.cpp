#include "casediagnosis.h"

#include <stdexcept>

CaseDiagnosis::CaseDiagnosis(const QString& diagnosis) {
    if (diagnosis.isEmpty()) {
        throw std::invalid_argument("诊断结果不能为空");
    }
    this->diagnosis = diagnosis;
}

const QString& CaseDiagnosis::getValue() const {
    return diagnosis;
}
