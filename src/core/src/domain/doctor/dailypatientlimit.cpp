#include "dailypatientlimit.h"

#include <stdexcept>

DailyPatientLimit::DailyPatientLimit(int limit): limit(limit) {
    if (limit <= 0) {
        throw std::invalid_argument("单日患者上限必须大于 0");
    }
}

int DailyPatientLimit::getValue() const {
    return this->limit;
}
