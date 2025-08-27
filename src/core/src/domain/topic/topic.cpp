#include "topic.h"

Topic::Topic(Id topicId, QList<Id> participants)
    : topicId(topicId), participants(participants) {}

const Id& Topic::getTopicId() const {
    return topicId;
}

const QList<Id>& Topic::getParticipants() const {
    return participants;
}
