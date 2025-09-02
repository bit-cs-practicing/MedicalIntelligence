#ifndef PATIENTREGISTER_H
#define PATIENTREGISTER_H

#include <QWidget>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
namespace Ui {
class PatientRegister;
}
class PatientLogin;
class PatientRegister : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRegister(QWidget *parent = nullptr, RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    void setLoginBoard(PatientLogin *tmp) {loginBoard = tmp;}
    ~PatientRegister();

private slots:
    void on_register_2_clicked();
    void on_returnBtn_clicked();
private:
    Ui::PatientRegister *ui;
    PatientLogin *loginBoard;
    CredentialManager *patientCredential;
    RpcClient *requestSender;
};

#endif // PATIENTREGISTER_H
