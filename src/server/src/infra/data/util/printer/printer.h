#ifndef PRINTER_H
#define PRINTER_H

#include <optional>

#include "domain/attendance/attendance.h"
#include "domain/doctor/doctor.h"
#include "domain/patient/patient.h"
#include "domain/appointment/appointment.h"
#include "domain/case/case.h"
#include "domain/leave/leaverecord.h"
#include "domain/message/message.h"
#include "infra/data/topic/topicparticipant.h"
#include "infra/data/topic/topictime.h"

class Printer {
public:
    static void printPatient(const std::optional<Patient>& obj);
    static void printDoctor(const std::optional<Doctor>& obj);
    static void printAttendance(const std::optional<Attendance>& obj);
    static void printAppointment(const std::optional<Appointment>& obj);
    static void printCase(const std::optional<Case>& obj);
    static void printLeaveRecord(const std::optional<LeaveRecord>& obj);
    static void printMessage(const std::optional<Message>& obj);
    static void printTopicParticipate(const std::optional<TopicParticipant>& obj);
    static void printTopicTime(const std::optional<TopicTime>& obj);
};

#endif // PRINTER_H
