#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#include <QString>

#include "../../domain/id.h"

class Credential {
public:
    Credential(Id userId, QString token);

    static Credential fromUserId(Id userId);

    const QString& getUserId() const;
    QString getRole() const;
    QString toString() const;
private:
    Id userId;
    QString token;
};

#endif // CREDENTIAL_H
