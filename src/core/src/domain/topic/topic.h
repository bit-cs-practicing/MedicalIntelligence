#ifndef TOPIC_H
#define TOPIC_H

#include <QList>
#include <QDateTime>

#include "../id.h"

class Topic {
public:
    explicit Topic(Id topicId, QList<Id> participants);

    const Id& getTopicId() const;
    const QList<Id>& getParticipants() const;
    const QDateTime& getLastMessageTime() const;

    void setLastMessageTime(QDateTime value);

private:
    Id topicId;
    QList<Id> participants;
    QDateTime lastMessageTime;
};

#endif // TOPIC_H
