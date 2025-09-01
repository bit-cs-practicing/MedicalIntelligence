#ifndef MESSAGESQLITEREPOSITORY_H
#define MESSAGESQLITEREPOSITORY_H

#include "domain/message/messagerepository.h"

#include <QtSql>

class MessageSQLiteRepository : public MessageRepository
{
public:
    MessageSQLiteRepository(const QUrl& path);
    ~MessageSQLiteRepository();
    void save(const Message& message) override;
    QList<Message> getAllByTopicIdOrderedByTime(const Id& topicId, int start, int limit) const override;
private:
    QSqlDatabase db;
};

#endif // MESSAGESQLITEREPOSITORY_H
