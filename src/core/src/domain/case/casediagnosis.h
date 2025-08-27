#ifndef CASEDIAGNOSIS_H
#define CASEDIAGNOSIS_H

#include <QString>

class CaseDiagnosis {
public:
    explicit CaseDiagnosis(const QString& diagnosis);

    const QString& getValue() const;

private:
    QString diagnosis;
};

#endif // CASEDIAGNOSIS_H
