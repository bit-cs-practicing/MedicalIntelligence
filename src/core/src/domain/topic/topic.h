#ifndef TOPIC_H
#define TOPIC_H

#include <QList>

#include "../id.h"

class Topic {
public:
    explicit Topic(Id topicId, QList<Id> participants);

    const Id& getTopicId() const;
    const QList<Id>& getParticipants() const;

private:
    Id topicId;
    QList<Id> participants;
};

#endif // TOPIC_H
