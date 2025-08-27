#include "id.h"

#include <QUuid>

Id::Id(QString id): id(id) {

}

Id Id::fromUuid() {
    QUuid uuid = QUuid::createUuid();
    return Id(uuid.toString());
}

const QString& Id::getId() const {
    return id;
}
