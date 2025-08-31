#ifndef TOPICDATABRIEF_H
#define TOPICDATABRIEF_H

#include <QWidget>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"

namespace Ui {
class TopicDataBrief;
}

class TopicDataDetails;

class TopicDataBrief : public QWidget
{
    Q_OBJECT

public:
    explicit TopicDataBrief(QWidget *parent = nullptr, QString patientUserId = "", RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    void setTopicInfo(QString S1, QString S2);
    ~TopicDataBrief();

private slots:
    void on_details_clicked();

private:
    Ui::TopicDataBrief *ui;
    QString patientUserId;
    CredentialManager *patientCredential;
    RpcClient *requestSender;
//    TopicDataDetails *detailWindow;
};

#endif // TOPICDATABRIEF_H
