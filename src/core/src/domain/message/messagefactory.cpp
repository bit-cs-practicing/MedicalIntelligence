#include "messagefactory.h"

#include <stdexcept>
#include <QDateTime>

MessageFactory::MessageFactory(std::shared_ptr<TopicRepository> topicRepository)
    : topicRepository(topicRepository)
{
}

Message MessageFactory::createMessage(const User &sender, const Topic& topic, MessageContent content) const {
    checkSenderInTopic(sender, topic);
    return Message(
        Id::fromUuid(),
        topic.getTopicId(),
        sender.getId(),
        sender.getName(),
        content,
        QDateTime::currentDateTime()
    );
}

void MessageFactory::checkSenderInTopic(const User &sender, const Topic& topic) const {
    if (!topic.getParticipants().contains(sender.getId())) {
        throw std::logic_error("用户不在话题群聊中，不可以发送消息");
    }
}
