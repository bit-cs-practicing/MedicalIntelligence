#ifndef CONSULTATIONQUESTION_H
#define CONSULTATIONQUESTION_H

#include <QString>

class ConsultationQuestion {
public:
    ConsultationQuestion(QString value);

    const QString& getValue() const;
private:
    QString value;
};

#endif // CONSULTATIONQUESTION_H
