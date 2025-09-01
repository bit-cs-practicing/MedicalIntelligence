#ifndef CASETUPLE_H
#define CASETUPLE_H

#include <QWidget>
#include "doctor.h"

namespace Ui {
class CaseTuple;
}

class CaseTuple : public QWidget
{
    Q_OBJECT

public:
    explicit CaseTuple(QString, QString, QString, QString, QString, QWidget *parent = nullptr);
    void setFatherMainWindow(Doctor *p) { fatherMainWindow = p; }
    ~CaseTuple();

private:
    Ui::CaseTuple *ui;
    Doctor *fatherMainWindow;
};

#endif // CASETUPLE_H
