#include "messagefactory.h"

#include <stdexcept>
#include <cassert>
#include <QDateTime>

MessageFactory::MessageFactory(std::shared_ptr<TopicRepository> topicRepository)
    : topicRepository(topicRepository)
{
}

Message MessageFactory::createMessage(const User &sender, Topic* topic, MessageContent content) const {
    assert(topic != nullptr);
    checkSenderInTopic(sender, *topic);
    auto message = Message(
        Id::fromUuid(),
        topic->getTopicId(),
        sender.getId(),
        sender.getName(),
        content,
        QDateTime::currentDateTime()
    );
    topic->setLastMessageTime(message.getTime());
    return message;
}

void MessageFactory::checkSenderInTopic(const User &sender, const Topic& topic) const {
    if (!topic.getParticipants().contains(sender.getId())) {
        throw std::logic_error("用户不在话题群聊中，不可以发送消息");
    }
}
