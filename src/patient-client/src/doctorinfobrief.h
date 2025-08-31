#ifndef DOCTORINFOBRIEF_H
#define DOCTORINFOBRIEF_H

#include <QWidget>
#include <memory>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
namespace Ui {
class DoctorInfoBrief;
}

class MainWindow;

class DoctorInfoBrief : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorInfoBrief(QWidget *parent = nullptr, RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    ~DoctorInfoBrief();
    void setDoctorBriefInfo(QString, QString, QString);
    void setFatherMainWindow(MainWindow *p) {fatherMainWindow = p;}

private slots:
    void on_details_clicked();

    void on_pushButton_clicked();

private:
    Ui::DoctorInfoBrief *ui;
    MainWindow *fatherMainWindow;
    CredentialManager *patientCredential;
    RpcClient *requestSender;
};

#endif // DOCTORINFOBRIEF_H
