#ifndef PRINTER_H
#define PRINTER_H

#include "core/src/domain/patient/patient.h"
#include "core/src/domain/doctor/doctor.h"

#include <optional>

class Printer
{
public:
    static void printPatient(const std::optional<Patient>& obj);
    static void printDoctor(const std::optional<Doctor>& obj);
};

#endif // PRINTER_H
