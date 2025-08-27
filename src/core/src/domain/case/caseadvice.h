#ifndef CASEADVICE_H
#define CASEADVICE_H

#include <QString>

class CaseAdvice {
public:
    explicit CaseAdvice(const QString& advice);

    const QString& getValue() const;

private:
    QString advice;
};

#endif // CASEADVICE_H
