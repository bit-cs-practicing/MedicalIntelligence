#include "message.h"

Message::Message(Id messageId, Id senderId, Name senderName, MessageContent content, QDateTime time)
    : messageId(messageId), senderId(senderId), senderName(senderName), content(content), time(time) {}

const Id& Message::getMessageId() const {
    return messageId;
}

const Id& Message::getSenderId() const {
    return senderId;
}

const Name& Message::getSenderName() const {
    return senderName;
}

const MessageContent& Message::getContent() const {
    return content;
}

const QDateTime& Message::getTime() const {
    return time;
}
