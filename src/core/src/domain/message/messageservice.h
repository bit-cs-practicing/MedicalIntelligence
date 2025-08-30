#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <memory>

#include <QList>

#include "domain/topic/topic.h"
#include "domain/user/user.h"

#include "message.h"
#include "messagerepository.h"

class MessageService {
public:
    MessageService(std::shared_ptr<MessageRepository> messageRepository);

    QList<Message> fetchMessages(const User& user, const Topic& topic, int start, int limit) const;
private:
    std::shared_ptr<MessageRepository> messageRepository;

    void checkPaging(int start, int limit) const;
    void checkUserInTopic(const User& user, const Topic& topic) const;
};

#endif // MESSAGESERVICE_H
