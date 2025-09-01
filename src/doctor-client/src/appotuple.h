#ifndef APPOTUPLE_H
#define APPOTUPLE_H

#include <QWidget>
#include "doctor.h"

namespace Ui {
class appoTuple;
}

class appoTuple : public QWidget
{
    Q_OBJECT

public:
    explicit appoTuple(QString, QString appoId, QString patientName, QString patientIdCard, QString date, QString timeSlot, QString status, QWidget *parent = nullptr);
    void setFatherMainWindow(Doctor *p) { fatherMainWindow = p; }
    void updateStatus(const QString &status);
    ~appoTuple();

signals:
    void pushBtn(QString appoId, QString status, QString pId);
    void pushBtn2(QString patientId);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::appoTuple *ui;
    QString m_appoId, patientId;
    QString m_currentStatus;
    Doctor *fatherMainWindow;
};

#endif // APPOTUPLE_H
