#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>

#include "../id.h"
#include "../user/name.h"
#include "messagecontent.h"

class Message {
public:
    explicit Message(Id messageId, Id senderId, Name senderName, MessageContent content, QDateTime time);

    const Id& getMessageId() const;
    const Id& getSenderId() const;
    const Name& getSenderName() const;
    const MessageContent& getContent() const;
    const QDateTime& getTime() const;

private:
    Id messageId;
    Id senderId;
    Name senderName;
    MessageContent content;
    QDateTime time;
};

#endif // MESSAGE_H
