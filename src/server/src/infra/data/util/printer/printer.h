#ifndef PRINTER_H
#define PRINTER_H

#include "domain/patient/patient.h"
#include "domain/doctor/doctor.h"
#include "domain/attendance/attendance.h"

#include <optional>

class Printer
{
public:
    static void printPatient(const std::optional<Patient>& obj);
    static void printDoctor(const std::optional<Doctor>& obj);
    static void printAttendance(const std::optional<Attendance>& obj);
};

#endif // PRINTER_H
