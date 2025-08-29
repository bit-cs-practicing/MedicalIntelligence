#ifndef TOPICFACTORY_H
#define TOPICFACTORY_H

#include <memory>
#include <QList>

#include "../patient/patient.h"
#include "../patient/patientrepository.h"
#include "../doctor/doctor.h"
#include "../doctor/doctorrepository.h"
#include "topic.h"

class TopicFactory {
public:
    TopicFactory(
        std::shared_ptr<PatientRepository> patientRepository,
        std::shared_ptr<DoctorRepository> doctorRepository
    );

    Topic createTopic(const Doctor& creator, QList<Id> participants) const;
private:
    std::shared_ptr<PatientRepository> patientRepository;
    std::shared_ptr<DoctorRepository> doctorRepository;
};

#endif // TOPICFACTORY_H
