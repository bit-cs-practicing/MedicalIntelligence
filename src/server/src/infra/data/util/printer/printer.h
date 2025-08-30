#ifndef PRINTER_H
#define PRINTER_H

#include "core/src/domain/patient/patient.h"

#include <optional>

class Printer
{
public:
    static void printPatient(const std::optional<Patient>& obj);
};

#endif // PRINTER_H
