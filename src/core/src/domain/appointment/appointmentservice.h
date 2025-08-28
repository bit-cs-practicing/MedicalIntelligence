#ifndef APPOINTMENTSERVICE_H
#define APPOINTMENTSERVICE_H

#include "appointment.h"
#include "../doctor/doctor.h"
#include "../patient/patient.h"

class AppointmentService {
public:
    AppointmentService();

    void completeAppointment(Appointment* appointment, const Doctor& doctor) const;
    void cancelAppointment(Appointment* appointment, const Patient& patient) const;
};

#endif // APPOINTMENTSERVICE_H
