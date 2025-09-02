#include "patientappointment.h"
#include "ui_patientappointment.h"
#include <QDebug>
#include <QJsonObject>
#include <QMessageBox>
PatientAppointment::PatientAppointment(QWidget *parent, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::PatientAppointment), patientCredential(pC), requestSender(rSender)
{
    ui->setupUi(this);
    ui->startTime->setDisplayFormat("HH:mm");
    ui->endTime->setDisplayFormat("HH:mm");
    ui->endTime->setTime(QTime(0, 29));
    ui->startTime->setReadOnly(true);
    ui->endTime->setReadOnly(true);
    ui->date->setDate(QDate::currentDate());
    connect(ui->timeSlider, &QSlider::valueChanged, this, [&](int x){
        if(x >= 96) {
            ui->startTime->setTime(QTime(23, 30));
            ui->endTime->setTime(QTime(23, 59));
        }
        else {
            ui->startTime->setTime(QTime(x / 4, (x / 2 & 1) ? 30 : 0));
            ui->endTime->setTime(QTime(x / 4, (x / 2 & 1) ? 59 : 29));
        }
    });
}

PatientAppointment::~PatientAppointment()
{
    delete ui;
}

void PatientAppointment::setDoctorInformation(QString name, QString id, QString sId){
    ui->doctorName->setText(name);
    ui->doctorId->setText(id);
    sendDoctorId = sId;
}

void PatientAppointment::on_closeWindow_clicked()
{
    this->close();
}

void PatientAppointment::on_submit_clicked()
{
    QJsonObject submitAppointment;
    submitAppointment["doctorId"] = sendDoctorId;
    submitAppointment["date"] = ui->date->date().toString("yyyy-MM-dd");
    submitAppointment["timeSlot"] = ui->startTime->time().toString("HH:mm") + "-" + ui->endTime->time().toString("HH:mm");
//    qDebug() << submitAppointment["date"] << "\n" << submitAppointment["timeSlot"] << "\n";
    Response result = requestSender->rpc(Request("appointment.create", patientCredential->get(), submitAppointment));
    qDebug() << result.data << "\n";
    if(result.success) {
        QMessageBox::information(this, "恭喜！", "预约成功！");
        this->close();
    }
    else {
        QMessageBox::warning(this, "警告！", "该时间段已被预约。");
    }
}
