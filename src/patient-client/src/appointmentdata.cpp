#include "appointmentdata.h"
#include "ui_appointmentdata.h"
#include <QJsonObject>
#include <QMessageBox>
AppointmentData::AppointmentData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppointmentData)
{
    ui->setupUi(this);
    ui->doctorId->setReadOnly(true);
    ui->appId->setReadOnly(true);
    ui->dateTime->setReadOnly(true);
    ui->status->setEnabled(false);
}

AppointmentData::~AppointmentData()
{
    delete ui;
}

void AppointmentData::setAppointmentData(QString appId, QString doctorId, QString date, QString time, QString status) {
    ui->appId->setText(appId);
    ui->doctorId->setText(doctorId);
    ui->dateTime->setText(date + " " + time);
    ui->status->setCurrentText(status);
    if(status == "scheduled") ui->cancelBtn->setEnabled(true);
    else ui->cancelBtn->setEnabled(false);
}

void AppointmentData::on_cancelBtn_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "确认操作",
        "您确认取消预约吗？",
        QMessageBox::Yes | QMessageBox::No
    );
    if(reply == QMessageBox::No) return;
    QJsonObject cancelApplication;
    cancelApplication["appointmentId"] = ui->appId->text();

    bool flag = true;
    if(flag) QMessageBox::information(this, "Congratulations!", "取消成功");
    else QMessageBox::warning(this, "Warning", "取消失败");
}
