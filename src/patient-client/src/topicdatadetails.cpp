#include "topicdatadetails.h"
#include "ui_topicdatadetails.h"
#include "doctormessage.h"
#include "patientmessage.h"
#include "customtextedit.h"
#include "triggerclosewindow.h"
#include <QDebug>
#include <QTimer>
#include <QJsonObject>
#include <QList>
#include <QMessageBox>
TopicDataDetails::TopicDataDetails(QWidget *parent, QString S, QString Id, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::TopicDataDetails),
    topicId(S), patientUserId(Id), patientCredential(pC), requestSender(rSender)
{
    ui->setupUi(this);
    loadMessageInfo();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&](){
        loadMessageInfo();
    });
    timer->start(10000);
    connect(ui->message, &CustomTextEdit::sendMessage, this, &TopicDataDetails::sendMessage);
    connect(this, &QWidget::destroyed, this, [&](){
        this->deleteLater();
        this->close();
    });
}

void TopicDataDetails::closeEvent(QCloseEvent *event){
//    qDebug() << "Yeah!Yeah!Yeah!\n";
    this->deleteLater();
    event->accept();
}

void TopicDataDetails::loadMessageInfo() {
    qDebug() << "loading message\n";
    QJsonObject fetchMessage = QJsonObject{
        {"topicId", topicId}, {"start", QString("0")}, {"limit", QString("100")}
    };

    Response result = requestSender->rpc(Request("chat.fetchMessages", patientCredential->get(), fetchMessage));
    qDebug() << result.data << "\n";
    if(!result.success) return;

//    messageInformations.clear();
//    while(!messageInformations.empty()) messageInformations.removeAt(0);
    messageInformations = result.data["messages"].toArray();

    showMessage();
}

void TopicDataDetails::showMessage() {
    QWidget *scrollContent = new QWidget(this);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(scrollLayout);
    for(QJsonValue i : messageInformations) {
        if(i["senderId"].toString() == patientUserId){
            PatientMessage *p = new PatientMessage(scrollContent, this);
            p->setPatientMessage(i["senderName"].toString(), i["content"].toString());
            if(i["messageId"] == "null") p->setTextEnabled(false);
            scrollLayout->addWidget(p);
        }
        else {
            DoctorMessage *p = new DoctorMessage(scrollContent, this);
            p->setDoctorMessage(i["senderName"].toString(), i["content"].toString());
            scrollLayout->addWidget(p);
        }
    }
    ui->screen->setWidget(scrollContent);
    ui->screen->setWidgetResizable(true);
}

void TopicDataDetails::sendMessage() {
    QJsonObject sendOutMessage = QJsonObject{
        {"topicId", topicId}, {"content", ui->message->toPlainText()}
    };
    QJsonObject tempAddMessage = QJsonObject{
        {"messageId", QString("null")}, {"senderId", patientUserId}, {"senderName", QString("Sending")},
        {"content", ui->message->toPlainText()}, {"time", QString("2025-09-01T10:10:03")}
    };
    ui->message->setText("");
    messageInformations.append(tempAddMessage);
    showMessage();
}

TopicDataDetails::~TopicDataDetails()
{
//    qDebug() << "closed\n";
    delete ui;
}

