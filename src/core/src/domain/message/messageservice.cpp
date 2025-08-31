#include "messageservice.h"

MessageService::MessageService(std::shared_ptr<MessageRepository> messageRepository)
    : messageRepository(messageRepository)
{
}

QList<Message> MessageService::fetchMessages(const User &user, const Topic &topic, int start, int limit) const {
    checkPaging(start, limit);
    checkUserInTopic(user, topic);
    auto messages = messageRepository->getAllByTopicIdOrderedByTime(topic.getTopicId(), start, limit);
    return messages;
}

void MessageService::checkPaging(int start, int limit) const {
    if (start < 0) {
        throw std::invalid_argument("起始消息偏移量不可以为负数");
    }
    if (limit < 0) {
        throw std::invalid_argument("获取消息数不可以为负数");
    }
}

void MessageService::checkUserInTopic(const User &user, const Topic& topic) const {
    if (!topic.getParticipants().contains(user.getId())) {
        throw std::logic_error("用户不在话题群聊中，不可以查看消息");
    }
}
