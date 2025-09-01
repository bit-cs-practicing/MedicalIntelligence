#include "chatappserviceimpl.h"

#include <QJsonArray>
#include <QList>

ChatAppServiceImpl::ChatAppServiceImpl(
    std::shared_ptr<TopicRepository> topicRepository,
    std::shared_ptr<TopicFactory> topicFactory,
    std::shared_ptr<MessageRepository> messageRepository,
    std::shared_ptr<MessageFactory> messageFactory,
    std::shared_ptr<MessageService> messageService,
    std::shared_ptr<PatientRepository> patientRepository,
    std::shared_ptr<DoctorRepository> doctorRepository,
    std::shared_ptr<CredentialRegistry> credentialRegistry
)
    : topicRepository(std::move(topicRepository))
    , topicFactory(std::move(topicFactory))
    , messageRepository(std::move(messageRepository))
    , messageFactory(std::move(messageFactory))
    , messageService(std::move(messageService))
    , patientRepository(std::move(patientRepository))
    , doctorRepository(std::move(doctorRepository))
    , credentialRegistry(std::move(credentialRegistry))
{
}

QJsonObject ChatAppServiceImpl::createTopic(const Credential& credential, const QJsonObject& data) {
    credentialRegistry->check(credential);

    auto doctorId = Id(credential.getUserId());
    auto doctorOpt = doctorRepository->getById(doctorId);
    if (!doctorOpt.has_value()) {
        throw std::logic_error("无效医生登录凭证");
    }
    auto doctor = doctorOpt.value();

    auto participantsJson = data["participants"].toArray();
    auto participants = QList<Id>();
    for (const auto& participant : participantsJson) {
        participants.push_back(Id(participant.toString()));
    }

    auto topic = topicFactory->createTopic(doctor, participants);
    topicRepository->save(topic);

    return QJsonObject {
        { "topicId", topic.getTopicId().getId() }
    };
}

QJsonObject ChatAppServiceImpl::listTopicsByUser(const Credential& credential, const QJsonObject&) const {
    credentialRegistry->check(credential);

    auto userId = Id(credential.getUserId());

    auto topics = topicRepository->getAllByContainingParticipantId(userId);

    auto topicsJson = QJsonArray();
    for (const auto& topic : topics) {
        auto topicJson = QJsonObject {
            { "topicId", topic.getTopicId().getId() },
            { "lastMessageTime", topic.getLastMessageTime().toString("yyyy-MM-ddTHH:mm:ss"), }
        };
        topicsJson.push_back(topicJson);
    }

    return QJsonObject {
        { "topics", topicsJson }
    };
}

QJsonObject ChatAppServiceImpl::sendMessage(const Credential& credential, const QJsonObject& data) {
    credentialRegistry->check(credential);

    auto userId = Id(credential.getUserId());
    auto user = getUserById(userId);

    auto topicId = Id(data["topicId"].toString());
    auto topicOpt = topicRepository->getById(topicId);
    if (!topicOpt.has_value()) {
        throw std::logic_error("话题不存在");
    }
    auto topic = topicOpt.value();

    auto content = MessageContent(data["content"].toString());

    auto message = messageFactory->createMessage(*user, &topic, content);
    messageRepository->save(message);

    return QJsonObject {
        { "messageId", message.getMessageId().getId() },
        { "time", message.getTime().toString("yyyy-MM-ddTHH:mm:ss") }
    };
}

QJsonObject ChatAppServiceImpl::fetchMessages(const Credential& credential, const QJsonObject& data) const {
    credentialRegistry->check(credential);

    auto userId = Id(credential.getUserId());
    auto user = getUserById(userId);

    auto topicId = Id(data["topicId"].toString());
    auto topicOpt = topicRepository->getById(topicId);
    if (!topicOpt.has_value()) {
        throw std::logic_error("话题不存在");
    }
    auto topic = topicOpt.value();

    auto start = data["start"].toInt();
    auto limit = data["limit"].toInt();

    auto messages = messageService->fetchMessages(*user, topic, start, limit);

    auto messagesJson = QJsonArray();
    for (const auto& message : messages) {
        auto messageJson = QJsonObject {
            { "messageId", message.getMessageId().getId() },
            { "senderId", message.getSenderId().getId() },
            { "senderName", message.getSenderName().getValue() },
            { "content", message.getContent().getContent() },
            { "time", message.getTime().toString("yyyy-MM-ddTHH:mm:ss") }
        };
        messagesJson.push_back(messageJson);
    }
    return QJsonObject {
        { "messages", messagesJson }
    };
}

std::unique_ptr<User> ChatAppServiceImpl::getUserById(const Id &userId) const {
    auto doctorOpt = doctorRepository->getById(userId);
    if (doctorOpt.has_value()) {
        return std::make_unique<Doctor>(doctorOpt.value());
    }
    auto patientOpt = patientRepository->getById(userId);
    if (patientOpt.has_value()) {
        return std::make_unique<Patient>(patientOpt.value());
    }
    throw std::logic_error("不存在此用户");
}
