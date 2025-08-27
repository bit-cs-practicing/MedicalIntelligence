#ifndef MESSAGECONTENT_H
#define MESSAGECONTENT_H

#include <QString>

class MessageContent {
public:
    explicit MessageContent(QString content);

    const QString& getContent() const;

private:
    QString content;
};

#endif // MESSAGECONTENT_H
