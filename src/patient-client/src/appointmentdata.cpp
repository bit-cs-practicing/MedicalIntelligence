#include "appointmentdata.h"
#include "ui_appointmentdata.h"

#include <QJsonObject>
#include <QMessageBox>

AppointmentData::AppointmentData(QWidget *parent, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::AppointmentData), patientCredential(pC), requestSender(rSender)
{
    ui->setupUi(this);
    ui->doctorId->setReadOnly(true);
    ui->appId->setReadOnly(true);
    ui->dateTime->setReadOnly(true);
    ui->status->setEnabled(false);
}

AppointmentData::~AppointmentData() {
    delete ui;
}

QString transferStatusFromENtoZH(const QString& ENStatus) {
    if (ENStatus == "completed") {
        return "已完成";
    } else if (ENStatus == "scheduled"){
        return "已预约";
    } else {
        return "已撤销";
    }
}

void AppointmentData::setAppointmentData(
    const QString& doctorName,
    const QString& doctorId,
    const QString& date,
    const QString& time,
    const QString& status,
    const QString& appId) {
    ui->appId->setText(doctorName);
    ui->doctorId->setText(doctorId);
    ui->dateTime->setText(date + " " + time);
    ui->status->setCurrentText(transferStatusFromENtoZH(status));
    appointmentId = appId;
    if(status == "scheduled") ui->cancelBtn->setEnabled(true);
    else ui->cancelBtn->setEnabled(false);
}

void AppointmentData::on_cancelBtn_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "确认操作",
        "您确认取消预约吗？",
        QMessageBox::Yes | QMessageBox::No
    );
    if(reply == QMessageBox::No) return;
    QJsonObject cancelApplication;
    cancelApplication["appointmentId"] = appointmentId;

    Response result = requestSender->rpc(Request("appointment.cancel", patientCredential->get(), cancelApplication));
    qDebug() << result.data << "\n";
    if(result.success) QMessageBox::information(this, "恭喜!", "取消成功");
    else QMessageBox::warning(this, "警告！", "取消失败");
}
