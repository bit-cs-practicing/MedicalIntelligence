#ifndef TOPICDATADETAILS_H
#define TOPICDATADETAILS_H

#include <QWidget>
#include <QCloseEvent>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
#include <QJsonArray>
namespace Ui {
class TopicDataDetails;
}

class TopicDataDetails : public QWidget
{
    Q_OBJECT

public:
    explicit TopicDataDetails(QWidget *parent = nullptr, QString S = "", QString T = "", RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    ~TopicDataDetails();
    void loadMessageInfo();
private slots:
    void on_sendBtn_clicked();
private:
    Ui::TopicDataDetails *ui;
    QString topicId, patientUserId;
    void showMessage();
    void sendMessage();
    QJsonArray messageInformations;
    CredentialManager *patientCredential;
    RpcClient *requestSender;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // TOPICDATADETAILS_H
