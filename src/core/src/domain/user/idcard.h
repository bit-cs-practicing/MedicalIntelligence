#ifndef IDCARD_H
#define IDCARD_H

#include <QString>

class IdCard {
public:
    explicit IdCard(QString id);

    const QString& getValue() const;
private:
    QString id;
};

#endif // IDCARD_H
