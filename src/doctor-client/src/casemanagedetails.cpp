#include "casemanagedetails.h"
#include "ui_casemanagedetails.h"
#include <QMessageBox>
#include <QJsonArray>
CaseManageDetails::CaseManageDetails(QWidget *parent, RpcClient *rClient, CredentialManager *cR, QJsonObject tmp) :
    QWidget(parent),
    ui(new Ui::CaseManageDetails), doctorCredential(cR), requestSender(rClient), appointmentDetails(tmp)
{
    ui->setupUi(this);
    ui->date->setReadOnly(true);
    ui->date->setDate(QDate::currentDate());
//    qDebug() << appointmentDetails;
    if(appointmentDetails["status"] != "scheduled") {
        Response result = requestSender->rpc(Request("case.fetchByAppointment", doctorCredential->get(), QJsonObject{{"appointmentId", appointmentDetails["appointmentId"].toString()}}));
        qDebug() << result.data;
        if(!result.success) {
            QMessageBox::warning(this, "Warning", result.message);
            this->close();
        }
        ui->diagnosis->setText(result.data["diagnosis"].toString());
        ui->prescription->setPlainText(result.data["prescription"].toString());
        ui->advice->setPlainText(result.data["advice"].toString());
        ui->date->setDate(QDate::fromString(result.data["visitDate"].toString(), "yyyy-MM-dd"));
        caseId = result.data["caseId"].toString();
    }
    ui->submit->setObjectName("okBtn");
}

CaseManageDetails::~CaseManageDetails()
{
    delete ui;
}

void CaseManageDetails::on_submit_clicked()
{
    if(appointmentDetails["status"].toString() == "scheduled") {
        QJsonObject sendData = QJsonObject{
            {"appointmentId", appointmentDetails["appointmentId"].toString()},
            {"diagnosis", ui->diagnosis->text()},
            {"prescription", ui->prescription->toPlainText()},
            {"advice", ui->advice->toPlainText()}
        };
        Response result = requestSender->rpc(Request("case.create", doctorCredential->get(), sendData));
        if(!result.success){
            QMessageBox::warning(this, "Warning", result.message);
            return;
        }
        QMessageBox::information(this, "Congratulations!", "创建病例成功！");
        result = requestSender->rpc(Request("appointment.complete", doctorCredential->get(), QJsonObject{{"appointmentId", appointmentDetails["appointmentId"].toString()}}));
        qDebug() << result.data;
        QJsonArray tmp;
        tmp.append(doctorCredential->get()->getUserId());
        tmp.append(appointmentDetails["patientId"].toString());
        result = requestSender->rpc(Request("chat.createTopic", doctorCredential->get(), QJsonObject{{"participants", tmp}}));
        qDebug() << result.data;
        return;
    }
    else {
        QJsonObject sendData = QJsonObject{
            {"caseId", caseId},
            {"diagnosis", ui->diagnosis->text()},
            {"prescription", ui->prescription->toPlainText()},
            {"advice", ui->advice->toPlainText()}
        };
        Response result = requestSender->rpc(Request("case.update", doctorCredential->get(), sendData));
        qDebug() << result.data;
        if(!result.success){
            QMessageBox::warning(this, "Warning", result.message);
            return;
        }
        QMessageBox::information(this, "Congratulations!", "创建病例成功！");
    }
}
