#ifndef TOPICSQLITEREPOSITORY_H
#define TOPICSQLITEREPOSITORY_H

#include "domain/topic/topicrepository.h"

#include <QtSql>

class TopicSQLiteRepository : public TopicRepository
{
public:
    TopicSQLiteRepository(const QString& path);
    ~TopicSQLiteRepository();
    void save(const Topic& topic) override;
    std::optional<Topic> getById(const Id& topicId) const override;
    QList<Topic> getAllByContainingParticipantId(const Id& participantId) const override;
private:
    QSqlDatabase db;
    void saveTopicParticipant(const Topic& topic);
    void saveTopicTime(const Topic& topic);
    QList<Id> getAllParticipantByTopicId(const Id& topicId) const;
};

#endif // TOPICSQLITEREPOSITORY_H
