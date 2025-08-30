#ifndef APPOINTMENTSERVICE_H
#define APPOINTMENTSERVICE_H

#include "domain/doctor/doctor.h"
#include "domain/patient/patient.h"

#include "appointment.h"

class AppointmentService {
public:
    AppointmentService();

    void completeAppointment(Appointment* appointment, const Doctor& doctor) const;
    void cancelAppointment(Appointment* appointment, const Patient& patient) const;
};

#endif // APPOINTMENTSERVICE_H
