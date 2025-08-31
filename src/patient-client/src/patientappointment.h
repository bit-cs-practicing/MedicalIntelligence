#ifndef PATIENTAPPOINTMENT_H
#define PATIENTAPPOINTMENT_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
namespace Ui {
class PatientAppointment;
}

class PatientAppointment : public QWidget
{
    Q_OBJECT

public:
    explicit PatientAppointment(QWidget *parent = nullptr, RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    void setDoctorInformation(QString, QString);
    ~PatientAppointment();

private slots:
    void on_closeWindow_clicked();

    void on_submit_clicked();

private:
    Ui::PatientAppointment *ui;
    CredentialManager *patientCredential;
    RpcClient *requestSender;

protected:
    void closeEvent(QCloseEvent *event) override {
//        qDebug() << "yesyeah\n";
        this->deleteLater();
        event->accept();
    }
};

#endif // PATIENTAPPOINTMENT_H
