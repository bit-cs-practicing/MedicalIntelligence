#ifndef DOCTORREGISTER_H
#define DOCTORREGISTER_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <memory>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class DoctorRegister; }
QT_END_NAMESPACE

class DoctorLogin;

class DoctorRegister : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorRegister( QWidget *parent = nullptr, RpcClient *rClient = nullptr, CredentialManager * cR = nullptr);
    void setLoginBoard( DoctorLogin *tmp ) {
        loginBoard = tmp;
    };
    ~DoctorRegister();

private slots:
    void on_registerBtn_clicked();

    void on_returnBtn_clicked();

private:
    Ui::DoctorRegister *ui;
    bool checkName();
    bool checkPassword();
    bool checkIdCard();
    DoctorLogin *loginBoard;
    CredentialManager *doctorCredential;
    RpcClient *requestSender;
};

#endif // DOCTORREGISTER_H
