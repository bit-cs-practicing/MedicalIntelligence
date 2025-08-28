#ifndef APPOINTMENTFACTORY_H
#define APPOINTMENTFACTORY_H

#include <memory>

#include "appointment.h"
#include "appointmentrepository.h"
#include "../patient/patient.h"
#include "../doctor/doctor.h"
#include "../doctor/doctorfactory.h"
#include "../leave/leaverecordrepository.h"

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
