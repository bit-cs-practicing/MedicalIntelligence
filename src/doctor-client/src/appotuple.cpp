#include "appotuple.h"
#include "ui_appotuple.h"

appoTuple::appoTuple(QString pId, QString appoId, QString patientName, QString patientIdCard, QString date, QString timeSlot, QString status, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appoTuple),
    m_appoId(appoId),
    m_currentStatus(status)
{
    patientId = pId;
    fatherMainWindow = nullptr;
    ui->setupUi(this);
    ui->patientName->setReadOnly(true);
    ui->patientIdCard->setReadOnly(true);
    ui->date->setReadOnly(true);
    ui->timeSlot->setReadOnly(true);
    ui->status->setReadOnly(true);
    if(status != "scheduled") ui->pushButton->setDisabled(true);
    ui->patientName->setText(patientName);
    ui->patientIdCard->setText(patientIdCard);
    ui->date->setText(date);
    ui->timeSlot->setText(timeSlot);
    ui->status->setText(status);
    m_appoId = appoId;
//    updateStatus(status);
}

appoTuple::~appoTuple()
{
    delete ui;
}

void appoTuple::on_pushButton_clicked()
{
    emit pushBtn(m_appoId, m_currentStatus, patientId);
}

void appoTuple::updateStatus(const QString &status) {
    m_currentStatus = status;

    if (status.toLower() == "scheduled") {
        ui->pushButton->setText("创建病历");
        ui->pushButton->setEnabled(true);
    }
    else if (status.toLower() == "completed") {
        ui->pushButton->setText("更新病历");
        ui->pushButton->setEnabled(true);
    }
    else {
        ui->pushButton->setText("无法创建病历");
        ui->pushButton->setEnabled(false);
    }
}

void appoTuple::on_pushButton_2_clicked()
{
    emit pushBtn2(patientId);
}
