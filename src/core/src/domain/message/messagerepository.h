#ifndef MESSAGEREPOSITORY_H
#define MESSAGEREPOSITORY_H

#include <optional>

#include <QList>

#include "message.h"

class MessageRepository {
public:
    virtual ~MessageRepository() = default;

    virtual void save(const Message& message) = 0;

    virtual QList<Message> getAllByTopicIdOrderedByTime(const Id& topicId, int start, int limit) const = 0;
};

#endif // MESSAGEREPOSITORY_H
