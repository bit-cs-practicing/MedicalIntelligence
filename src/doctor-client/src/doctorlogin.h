#ifndef DOCTORLOGIN_H
#define DOCTORLOGIN_H

#include <QMainWindow>
#include <QString>
#include <memory>
#include <QWidget>
#include "doctor.h"
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class DoctorLogin; }
QT_END_NAMESPACE

class DoctorRegister;

class DoctorLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorLogin(QWidget *parent = nullptr, RpcClient *rClient = nullptr, CredentialManager * cR = nullptr);
    ~DoctorLogin();

signals:
    void loginSucceed(QString emplyeeId);

public slots:
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();

private:
    Ui::DoctorLogin *ui;
    bool checkUsername();
    bool checkPassword();
    std::unique_ptr<DoctorRegister> registerBoard;
    std::unique_ptr<Doctor> doctorBoard;
    CredentialManager *doctorCredential;
    RpcClient *requestSender;
};
#endif // DOCTORLOGIN_H
