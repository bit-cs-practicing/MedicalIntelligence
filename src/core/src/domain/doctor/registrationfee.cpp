#include "registrationfee.h"

#include <stdexcept>

RegistrationFee::RegistrationFee(double fee): fee(fee) {
    if (fee <= 0) {
        throw std::invalid_argument("挂号费用必须大于 0");
    }
}

double RegistrationFee::getValue() const {
    return this->fee;
}
