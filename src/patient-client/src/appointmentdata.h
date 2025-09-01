#ifndef APPOINTMENTDATA_H
#define APPOINTMENTDATA_H

#include <QWidget>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
namespace Ui {
class AppointmentData;
}

class AppointmentData : public QWidget {
    Q_OBJECT

public:
    explicit AppointmentData(QWidget *parent = nullptr, RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    void setAppointmentData(QString doctorName, QString doctorId, QString date, QString time, QString status, QString appId);
    ~AppointmentData();

private slots:
    void on_cancelBtn_clicked();

private:
    Ui::AppointmentData *ui;
    CredentialManager *patientCredential;
    RpcClient *requestSender;
    QString appointmentId;
};

#endif // APPOINTMENTDATA_H
