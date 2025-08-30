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
TopicDataDetails::TopicDataDetails(QWidget *parent, QString S, QString Id) :
    QWidget(parent),
    ui(new Ui::TopicDataDetails),
    topicId(S), patientUserId(Id)
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

    bool flag = true;
    if(!flag) return;

    messageInformations.clear();
    QJsonObject messageData;
    messageData = QJsonObject{
        {"messageId", QString("M987654")}, {"senderId", QString("P0001")}, {"senderName", QString("Me")},
        {"content", QString("这是一条短消息")}, {"time", QString("2025-09-01T10:10:00")}
    };
    messageInformations.append(messageData);

    messageData = QJsonObject{
        {"messageId", QString("M987655")}, {"senderId", QString("D0001")}, {"senderName", QString("Wang")},
        {"content", QString("这是一条长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长消息")}, {"time", QString("2025-09-01T10:10:01")}
    };
    messageInformations.append(messageData);

    messageData = QJsonObject{
        {"messageId", QString("M987656")}, {"senderId", QString("P0001")}, {"senderName", QString("Me")},
        {"content", QString("这是一条长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长消息")}, {"time", QString("2025-09-01T10:10:02")}
    };
    messageInformations.append(messageData);

    messageData = QJsonObject{
        {"messageId", QString("M987657")}, {"senderId", QString("D0002")}, {"senderName", QString("Li")},
        {"content", QString("这是一条短消息")}, {"time", QString("2025-09-01T10:10:03")}
    };
    messageInformations.append(messageData);

    showMessage();
}

void TopicDataDetails::showMessage() {
    QWidget *scrollContent = new QWidget(this);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(scrollLayout);
    for(QJsonObject i : messageInformations) {
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

