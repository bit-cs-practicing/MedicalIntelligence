#include "topicfactory.h"

#include <stdexcept>
#include <QDateTime>

TopicFactory::TopicFactory(
    std::shared_ptr<PatientRepository> patientRepository,
    std::shared_ptr<DoctorRepository> doctorRepository
)
    : patientRepository(patientRepository)
    , doctorRepository(doctorRepository)
{
}

Topic TopicFactory::createTopic(const Doctor&, QList<Id> participants) const {
    auto patientNum = 0;
    auto doctorNum = 0;
    for (auto& id : participants) {
        if (doctorRepository->getById(id).has_value()) {
            doctorNum += 1;
        } else if (patientRepository->getById(id).has_value()) {
            patientNum += 1;
        }
    }
    if (patientNum != 1) {
        throw std::logic_error("话题群聊最多只能有一名患者");
    }
    if (patientNum + doctorNum != participants.length()) {
        throw std::logic_error("存在无效用户 ID");
    }
    return Topic(Id::fromUuid(), participants);
}
