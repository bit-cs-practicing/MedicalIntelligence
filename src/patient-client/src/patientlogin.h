#ifndef PATIENTLOGIN_H
#define PATIENTLOGIN_H
#include <memory>
#include <QWidget>
#include "patientregister.h"
#include "mainwindow.h"
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
namespace Ui {
class PatientLogin;
}

class PatientLogin : public QWidget
{
    Q_OBJECT

public:
    explicit PatientLogin(QWidget *parent = nullptr, RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    ~PatientLogin();

private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::PatientLogin *ui;
    bool checkUsername();
    bool checkPassword();
    std::unique_ptr<PatientRegister> registerBoard;
    std::unique_ptr<MainWindow> patientWindow;
    CredentialManager *patientCredential;
    RpcClient *requestSender;

//    PatientRegister *registerBoard;
};

#endif // PATIENTLOGIN_H
