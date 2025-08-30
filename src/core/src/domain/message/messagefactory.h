#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <memory>

#include "../user/user.h"
#include "../topic/topicrepository.h"
#include "message.h"

class MessageFactory {
public:
    MessageFactory(std::shared_ptr<TopicRepository> topicRepository);

    Message createMessage(const User& sender, Topic* topic, MessageContent content) const;
private:
    std::shared_ptr<TopicRepository> topicRepository;

    void checkSenderInTopic(const User& sender, const Topic& topic) const;
};

#endif // MESSAGEFACTORY_H
