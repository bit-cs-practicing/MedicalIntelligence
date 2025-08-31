#include "topicparticipant.h"

TopicParticipant::TopicParticipant(Id topicId, Id participantId) :
    topicId(topicId), participantId(participantId)
{
}

const Id& TopicParticipant::getTopicId() const {
    return topicId;
}
const Id& TopicParticipant::getParticipantId() const {
    return participantId;
}
