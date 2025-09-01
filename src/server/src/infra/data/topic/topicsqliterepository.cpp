#include "topicsqliterepository.h"

#include "infra/data/util/databaseoperator/databaseoperator.h"

TopicSQLiteRepository::TopicSQLiteRepository(const QUrl& path) {
    DatabaseOperator::createConnection(&db, "Topic", path);
}

TopicSQLiteRepository::~TopicSQLiteRepository() {
    db.close();
}

void TopicSQLiteRepository::saveTopicParticipant(const Topic& topic) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM topicParticipant WHERE topicId = :topicId;");
    query.bindValue(":topicId", topic.getTopicId().getId());
    bool result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";

    for (Id participantId: topic.getParticipants()) {
        query.prepare(
            "INSERT INTO topicParticipant(topicId,participantId) "
            "VALUES (:topicId,:participantId);"
        );
        query.bindValue(":topicId", topic.getTopicId().getId());
        query.bindValue(":participantId", participantId.getId());
        result = query.exec();
        qDebug() << query.lastQuery();
        if (result) qDebug() << "success";
        else qDebug() << "fail";
    }
}

void TopicSQLiteRepository::saveTopicTime(const Topic& topic) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM topic WHERE topicId = :topicId;");
    query.bindValue(":topicId", topic.getTopicId().getId());
    bool result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";

    query.prepare(
        "INSERT INTO topic(topicId,lastMessageTime) "
        "VALUES (:topicId,:lastMessageTime);"
    );
    query.bindValue(":topicId", topic.getTopicId().getId());
    query.bindValue(":lastMessageTime", topic.getLastMessageTime().toString(Qt::ISODate));
    result = query.exec();
    qDebug() << query.lastQuery();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
}

void TopicSQLiteRepository::save(const Topic& topic) {
    saveTopicParticipant(topic);
    saveTopicTime(topic);
}

QList<Topic> TopicSQLiteRepository::getAllByContainingParticipantId(const Id& participantId) const {
    QSqlQuery query(db);
    query.prepare("SELECT topicId FROM topicParticipant WHERE participantId = :participantId;");
    query.bindValue(":participantId", participantId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Id> topicIds;
    while(query.next())
        topicIds.push_back(Id(query.value(0).toString()));
    QList<Topic> topics;
    for (Id topicId: topicIds)
        topics.push_back(getById(topicId).value());
    return topics;
}

QList<Id> TopicSQLiteRepository::getAllParticipantByTopicId(const Id& topicId) const {
    QSqlQuery query(db);
    query.prepare("SELECT participantId FROM topicParticipant WHERE topicId = :topicId;");
    query.bindValue(":topicId", topicId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";
    QList<Id> que;
    while(query.next())
        que.push_back(Id(query.value(0).toString()));
    return que;
}

std::optional<Topic> TopicSQLiteRepository::getById(const Id& topicId) const {
    QSqlQuery query(db);
    query.prepare("SELECT lastMessageTime FROM topic WHERE topicId = :topicId;");
    query.bindValue(":topicId", topicId.getId());
    bool result = query.exec();
    if (result) qDebug() << "success";
    else qDebug() << "fail";

    if (!query.next()) return std::nullopt;
    QDateTime lastMessageTime(query.value(0).toDateTime());
    QList<Id> participants(getAllParticipantByTopicId(topicId));
    Topic topic(topicId, participants);
    topic.setLastMessageTime(lastMessageTime);
    return topic;
}
