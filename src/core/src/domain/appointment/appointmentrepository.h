#ifndef APPOINTMENTREPOSITORY_H
#define APPOINTMENTREPOSITORY_H

#include "appointment.h"
#include <optional>
#include <QList>

class AppointmentRepository {
public:
    virtual ~AppointmentRepository() = 0;

    virtual void save(const Appointment& appointment) = 0;
    virtual std::optional<Appointment> getById(const Id& appointmentId) = 0;
    virtual QList<Appointment> getAllByPatientId(const Id& patientId) = 0;
    virtual QList<Appointment> getAllByDoctorId(const Id& doctorId) = 0;
    virtual QList<Appointment> getAllByDoctorIdAndPatientId(const Id& doctorId, const Id& patientId) = 0;
};

#endif // APPOINTMENTREPOSITORY_H
