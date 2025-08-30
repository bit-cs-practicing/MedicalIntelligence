#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QDate>
#include <QString>

#include "domain/id.h"

#include "appointmentstatus.h"
#include "appointmenttimeslot.h"

class Appointment {
public:
    Appointment(
        Id appointmentId,
        Id doctorId,
        Id patientId,
        QDate date,
        AppointmentTimeSlot timeSlot
    );

    const Id& getAppointmentId() const;
    const Id& getDoctorId() const;
    const Id& getPatientId() const;
    const QDate& getDate() const;
    const AppointmentTimeSlot& getTimeSlot() const;
    const AppointmentStatus& getStatus() const;
    void markAsCompleted();
    void markAsCancelled();

private:
    Id appointmentId;
    Id doctorId;
    Id patientId;
    QDate date;
    AppointmentTimeSlot timeSlot;
    AppointmentStatus status;
};

#endif // APPOINTMENT_H
