#ifndef PRINTER_H
#define PRINTER_H

#include <optional>

#include "domain/attendance/attendance.h"
#include "domain/doctor/doctor.h"
#include "domain/patient/patient.h"

class Printer {
public:
    static void printPatient(const std::optional<Patient>& obj);
    static void printDoctor(const std::optional<Doctor>& obj);
    static void printAttendance(const std::optional<Attendance>& obj);
};

#endif // PRINTER_H
