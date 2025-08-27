#ifndef CASEPRESCRIPTION_H
#define CASEPRESCRIPTION_H

#include <QString>

class CasePrescription {
public:
    explicit CasePrescription(const QString& prescription);

    const QString& getValue() const;

private:
    QString prescription;
};

#endif // CASEPRESCRIPTION_H
