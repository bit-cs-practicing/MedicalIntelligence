#ifndef APPOINTMENTREPOSITORY_H
#define APPOINTMENTREPOSITORY_H

#include "appointment.h"
#include <optional>
#include <QList>

class AppointmentRepository {
public:
    virtual ~AppointmentRepository() = default;

    virtual void save(const Appointment& appointment) = 0;
    virtual std::optional<Appointment> getById(const Id& appointmentId) const = 0;
    virtual QList<Appointment> getAllByPatientId(const Id& patientId) const = 0;
    virtual QList<Appointment> getAllByDoctorId(const Id& doctorId) const = 0;
    virtual QList<Appointment> getAllByDoctorIdAndPatientId(const Id& doctorId, const Id& patientId) const = 0;
    virtual QList<Appointment> getAllByDoctorIdAndDate(const Id& doctorId, const QDate& date) const = 0;
};

#endif // APPOINTMENTREPOSITORY_H
