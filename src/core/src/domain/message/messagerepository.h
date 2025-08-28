#ifndef MESSAGEREPOSITORY_H
#define MESSAGEREPOSITORY_H

#include "message.h"
#include <optional>
#include <QList>

class MessageRepository {
public:
    virtual ~MessageRepository() = 0;

    virtual void save(const Message& message) = 0;

    virtual QList<Message> getAllByTopicIdOrderedByTime(const Id& topicId, int start, int limit) const = 0;
};

#endif // MESSAGEREPOSITORY_H
