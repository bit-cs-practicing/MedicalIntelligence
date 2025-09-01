#ifndef CONSULTATIONPROVIDER_H
#define CONSULTATIONPROVIDER_H

#include "consultationanswer.h"
#include "consultationquestion.h"

class ConsultationProvider {
public:
    virtual ~ConsultationProvider() = default;

    virtual ConsultationAnswer getAnswer(const ConsultationQuestion& question) const = 0;
};

#endif // CONSULTATIONPROVIDER_H
