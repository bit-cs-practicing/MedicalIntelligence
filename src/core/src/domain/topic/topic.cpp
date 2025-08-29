#include "topic.h"

Topic::Topic(Id topicId, QList<Id> participants)
    : topicId(topicId), participants(participants) {}

const Id& Topic::getTopicId() const {
    return topicId;
}

const QList<Id>& Topic::getParticipants() const {
    return participants;
}

const QDateTime& Topic::getLastMessageTime() const {
    return lastMessageTime;
}

void Topic::setLastMessageTime(QDateTime value) {
    lastMessageTime = value;
}
