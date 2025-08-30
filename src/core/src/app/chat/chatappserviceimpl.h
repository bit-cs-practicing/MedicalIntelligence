#ifndef CHATAPPSERVICEIMPL_H
#define CHATAPPSERVICEIMPL_H

#include <memory>

#include "../../domain/user/user.h"
#include "../../domain/patient/patient.h"
#include "../../domain/patient/patientrepository.h"
#include "../../domain/doctor/doctor.h"
#include "../../domain/doctor/doctorrepository.h"
#include "../../domain/topic/topicrepository.h"
#include "../../domain/topic/topicfactory.h"
#include "../../domain/message/message.h"
#include "../../domain/message/messagerepository.h"
#include "../../domain/message/messagefactory.h"
#include "../../domain/message/messageservice.h"
#include "../../infra/security/credentialregistry.h"
#include "chatappservice.h"

class ChatAppServiceImpl : public ChatAppService {
public:
    ChatAppServiceImpl(
        std::shared_ptr<TopicRepository> topicRepository,
        std::shared_ptr<TopicFactory> topicFactory,
        std::shared_ptr<MessageRepository> messageRepository,
        std::shared_ptr<MessageFactory> messageFactory,
        std::shared_ptr<MessageService> messageService,
        std::shared_ptr<PatientRepository> patientRepository,
        std::shared_ptr<DoctorRepository> doctorRepository,
        std::shared_ptr<CredentialRegistry> credentialRegistry
    );

    virtual QJsonObject createTopic(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject listTopicsByUser(const Credential& credential, const QJsonObject& data) const override;
    virtual QJsonObject sendMessage(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject fetchMessages(const Credential& credential, const QJsonObject& data) const override;
private:
    std::shared_ptr<TopicRepository> topicRepository;
    std::shared_ptr<TopicFactory> topicFactory;
    std::shared_ptr<MessageRepository> messageRepository;
    std::shared_ptr<MessageFactory> messageFactory;
    std::shared_ptr<MessageService> messageService;
    std::shared_ptr<PatientRepository> patientRepository;
    std::shared_ptr<DoctorRepository> doctorRepository;
    std::shared_ptr<CredentialRegistry> credentialRegistry;

    std::unique_ptr<User> getUserById(const Id& userId) const;
};

#endif // CHATAPPSERVICEIMPL_H
