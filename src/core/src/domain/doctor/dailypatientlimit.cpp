#include "dailypatientlimit.h"

#include <stdexcept>

DailyPatientLimit::DailyPatientLimit(int limit): limit(limit) {
    if (limit <= 0) {
        throw std::logic_error("单日患者上限必须大于 0");
    }
}

int DailyPatientLimit::getValue() const {
    return this->limit;
}
