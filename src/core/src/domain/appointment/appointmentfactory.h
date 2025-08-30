#ifndef APPOINTMENTFACTORY_H
#define APPOINTMENTFACTORY_H

#include <memory>

#include "domain/doctor/doctor.h"
#include "domain/doctor/doctorfactory.h"
#include "domain/leave/leaverecordrepository.h"
#include "domain/patient/patient.h"

#include "appointment.h"
#include "appointmentrepository.h"

class AppointmentFactory {
public:
    AppointmentFactory(
        std::shared_ptr<AppointmentRepository> appointmentRepository,
        std::shared_ptr<DoctorRepository> doctorRepository,
        std::shared_ptr<LeaveRecordRepository> leaveRecordRepository
    );

    Appointment createAppointment(
        const Doctor& doctor,
        const Patient& patient,
        QDate date,
        AppointmentTimeSlot timeSlot
    ) const;

private:
    std::shared_ptr<AppointmentRepository> appointmentRepository;
    std::shared_ptr<DoctorRepository> doctorRepository;
    std::shared_ptr<LeaveRecordRepository> leaveRecordRepository;

    void checkLeaveNotOverlapped(
        const Doctor& doctor,
        const QDate& date,
        const AppointmentTimeSlot& timeSlot
    ) const;

    void checkAppointmentNotFull(
        const Doctor& doctor,
        const QList<Appointment>& appointments
    ) const;

    void checkAppointmentNotOverlapped(
        const QList<Appointment>& appointments,
        const AppointmentTimeSlot& timeSlot
    ) const;
};

#endif // APPOINTMENTFACTORY_H
