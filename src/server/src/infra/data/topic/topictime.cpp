#include "topictime.h"

TopicTime::TopicTime(Id topicId, QDateTime lastMessageTime):
    topicId(topicId),lastMessageTime(lastMessageTime)
{
}

const Id& TopicTime::getTopicId() const {
    return topicId;
}

const QDateTime& TopicTime::getLastMessageTime() const {
    return lastMessageTime;
}
