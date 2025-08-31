#ifndef TOPICPARTICIPANT_H
#define TOPICPARTICIPANT_H

#include "domain/topic/topic.h"

class TopicParticipant
{
public:
    explicit TopicParticipant(Id topicId, Id ParticipantId);
    const Id& getTopicId() const;
    const Id& getParticipantId() const;
private:
    Id topicId;
    Id participantId;
};

#endif // TOPICPARTICIPANT_H
