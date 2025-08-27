#include "caseprescription.h"

#include <stdexcept>

CasePrescription::CasePrescription(const QString& prescription) {
    if (prescription.isEmpty()) {
        throw std::logic_error("处方不能为空");
    }
    this->prescription = prescription;
}

const QString& CasePrescription::getValue() const {
    return prescription;
}
