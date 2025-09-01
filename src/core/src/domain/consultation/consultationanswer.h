#ifndef CONSULTATIONANSWER_H
#define CONSULTATIONANSWER_H

#include <QString>

class ConsultationAnswer {
public:
    ConsultationAnswer(QString value);

    const QString& getValue() const;
private:
    QString value;
};

#endif // CONSULTATIONANSWER_H
