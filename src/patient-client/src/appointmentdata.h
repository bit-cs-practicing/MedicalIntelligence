#ifndef APPOINTMENTDATA_H
#define APPOINTMENTDATA_H

#include <QWidget>

namespace Ui {
class AppointmentData;
}

class AppointmentData : public QWidget {
    Q_OBJECT

public:
    explicit AppointmentData(QWidget *parent = nullptr);
    void setAppointmentData(QString appId, QString doctorId, QString date, QString time, QString status);
    ~AppointmentData();

private slots:
    void on_cancelBtn_clicked();

private:
    Ui::AppointmentData *ui;
};

#endif // APPOINTMENTDATA_H
