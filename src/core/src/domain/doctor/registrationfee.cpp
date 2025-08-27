#include "registrationfee.h"

#include <stdexcept>

RegistrationFee::RegistrationFee(double fee): fee(fee) {
    if (fee <= 0) {
        throw std::logic_error("挂号费用必须大于 0");
    }
}

double RegistrationFee::getValue() const {
    return this->fee;
}
