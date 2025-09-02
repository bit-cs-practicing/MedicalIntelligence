#ifndef CASEMANAGEDETAILS_H
#define CASEMANAGEDETAILS_H
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
#include <QWidget>

namespace Ui {
class CaseManageDetails;
}

class CaseManageDetails : public QWidget
{
    Q_OBJECT

public:
    explicit CaseManageDetails(QWidget *parent = nullptr, RpcClient *rClient = nullptr, CredentialManager * cR = nullptr, QJsonObject tmp = QJsonObject{});
    void setAppointmetnDetails(const QJsonObject& tmp){appointmentDetails = tmp;}
    ~CaseManageDetails();

private slots:
    void on_submit_clicked();

private:
    Ui::CaseManageDetails *ui;
    CredentialManager *doctorCredential;
    RpcClient *requestSender;
    QJsonObject appointmentDetails;
    QString caseId;
};

#endif // CASEMANAGEDETAILS_H
