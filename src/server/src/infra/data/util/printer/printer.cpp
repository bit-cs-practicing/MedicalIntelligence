#include "printer.h"

#include <QDebug>

void Printer::printPatient(const std::optional<Patient>& obj)
{
    if (!obj.has_value()) {
        qDebug() << "User aren't existed";
        return;
    }
    Patient p = obj.value();
    qDebug() << p.getId().getId() << '|' << p.getName().getValue() << '|'
             << p.getIdCard().getValue() << '|' << p.getGender().getValue() << '|'
             << p.getPhone().getValue();
}
