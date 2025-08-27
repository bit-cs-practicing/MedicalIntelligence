#include "caseadvice.h"

#include <stdexcept>

CaseAdvice::CaseAdvice(const QString& advice) {
    if (advice.isEmpty()) {
        throw std::logic_error("医嘱不能为空");
    }
    this->advice = advice;
}

const QString& CaseAdvice::getValue() const {
    return advice;
}
