#ifndef TOPICREPOSITORY_H
#define TOPICREPOSITORY_H

#include <optional>

#include <QList>

#include "topic.h"

class TopicRepository {
public:
    virtual ~TopicRepository() = default;

    virtual void save(const Topic& topic) = 0;
    virtual std::optional<Topic> getById(const Id& topicId) const = 0;
    virtual QList<Topic> getAllByContainingParticipantId(const Id& participantId) const = 0;
};

#endif // TOPICREPOSITORY_H
