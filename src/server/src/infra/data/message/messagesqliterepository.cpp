#include "messagesqliterepository.h"

#include "infra/data/util/databaseoperator/databaseoperator.h"

MessageSQLiteRepository::MessageSQLiteRepository(const QString& path) {
    DatabaseOperator::createConnection(&db, "Message", path);
}

MessageSQLiteRepository::~MessageSQLiteRepository() {
    db.close();
}

void MessageSQLiteRepository::save(const Message& message) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM message WHERE messageId = :messageId;");
    query.bindValue(":messageId", message.getMessageId().getId());
    bool result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";

    query.prepare(
        "INSERT INTO message(messageId,topicId,senderId,senderName,content,sendTime) "
        "VALUES (:messageId,:topicId,:senderId,:senderName,:content,:sendTime);"
    );
    query.bindValue(":messageId", message.getMessageId().getId());
    query.bindValue(":topicId", message.getTopicId().getId());
    query.bindValue(":senderId", message.getSenderId().getId());
    query.bindValue(":senderName", message.getSenderName().getValue());
    query.bindValue(":content", message.getContent().getContent());
    query.bindValue(":sendTime", message.getTime().toString(Qt::ISODate));
    result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
}
QList<Message> MessageSQLiteRepository::getAllByTopicIdOrderedByTime(const Id& topicId, int start, int limit) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM message WHERE topicId = :topicId ORDER BY sendTime ASC;");
    query.bindValue(":topicId", topicId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Message> que;
    while(query.next()) {
        que.push_back(DatabaseOperator::getMessageFromQuery(query));
    }
    for (int i = 1; i <= start && !que.empty(); i ++) {
        que.pop_back();
    }
    while(!que.empty() && que.size() > limit) {
        que.pop_front();
    }
    return que;
}
