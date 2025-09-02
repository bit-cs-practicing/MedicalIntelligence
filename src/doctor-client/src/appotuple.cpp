#include "appotuple.h"
#include "ui_appotuple.h"
#include "casemanagedetails.h"
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
//    if(status != "scheduled") ui->pushButton->setDisabled(true);
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


void appoTuple::on_pushButton_2_clicked()
{
    CaseManageDetails *p = new CaseManageDetails(nullptr, requestSender, doctorCredential, appointmentDetails);
    p->show();
}
