#include "topicdatabrief.h"
#include "topicdatadetails.h"
#include "ui_topicdatabrief.h"
//#include <QJsonObject>
#include <QDebug>
TopicDataBrief::TopicDataBrief(QWidget *parent, QString Id, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::TopicDataBrief), patientUserId(Id), patientCredential(pC), requestSender(rSender)
{
    ui->setupUi(this);
    ui->topicId->setReadOnly(true);
    ui->time->setReadOnly(true);
//    qDebug() << "created!\n";
}

TopicDataBrief::~TopicDataBrief()
{
//    qDebug() << "deleted!\n";
    delete ui;
}

void TopicDataBrief::setTopicInfo(QString S1, QString S2) {
    ui->topicId->setText(S1), ui->time->setText(S2);
}

void TopicDataBrief::on_details_clicked()
{
    //delete detailWindow;
    TopicDataDetails *p = new TopicDataDetails(nullptr, ui->topicId->text(), patientUserId, requestSender, patientCredential);
//    detailWindow->deleteLater();
    p->show();
}
