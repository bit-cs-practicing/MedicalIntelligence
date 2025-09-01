#ifndef APPOINTMENTSQLITEREPOSITORY_H
#define APPOINTMENTSQLITEREPOSITORY_H

#include "domain/appointment/appointmentrepository.h"

#include <QtSql>

class AppointmentSQLiteRepository : public AppointmentRepository
{
public:
    AppointmentSQLiteRepository(const QUrl& path);
    ~AppointmentSQLiteRepository();
    void save(const Appointment &appointment) override;
    std::optional<Appointment> getById(const Id& appointmentId) const override;
    QList<Appointment> getAllByPatientId(const Id& patientId) const override;
    QList<Appointment> getAllByDoctorId(const Id& doctorId) const override;
    QList<Appointment> getAllByDoctorIdAndPatientId(const Id& doctorId, const Id& patientId) const override;
    QList<Appointment> getAllByDoctorIdAndDate(const Id& doctorId, const QDate& date) const override;
private:
    QSqlDatabase db;
};

#endif // APPOINTMENTSQLITEREPOSITORY_H
