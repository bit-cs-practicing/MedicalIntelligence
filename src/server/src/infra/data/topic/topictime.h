#ifndef TOPICTIME_H
#define TOPICTIME_H

#include "domain/topic/topic.h"

class TopicTime
{
    explicit TopicTime(Id topicId, QDateTime lastMessageTime);
    const Id& getTopicId() const;
    const QDateTime& getLastMessageTime() const;
private:
    Id topicId;
    QDateTime lastMessageTime;
};

#endif // TOPICTIME_H
