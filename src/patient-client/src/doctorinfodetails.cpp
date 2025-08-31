#include "doctorinfodetails.h"
#include "ui_doctorinfodetails.h"
#include <QJsonObject>
DoctorInfoDetails::DoctorInfoDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorInfoDetails)
{
    ui->setupUi(this);
    ui->doctorId->setReadOnly(true);
    ui->depart->setReadOnly(true);
    ui->profile->setReadOnly(true);
    ui->photo->setReadOnly(true);
    ui->schedule->setReadOnly(true);
    ui->regFee->setReadOnly(true);
    ui->limit->setReadOnly(true);
    ui->name->setReadOnly(true);
}

DoctorInfoDetails::~DoctorInfoDetails()
{
    delete ui;
}

void DoctorInfoDetails::setInformations(QJsonObject info) {
    ui->doctorId->setText(info["employeeId"].toString());
    ui->depart->setText(info["department"].toString());
    ui->profile->setText(info["profile"].toString());
    ui->photo->setText(info["photo"].toString());
    ui->schedule->setText(info["workSchedule"].toString());
    ui->regFee->setText(QString::number(info["registrationFee"].toDouble()));
    ui->limit->setText(QString::number(info["dailyPatientLimit"].toInt()));
    ui->name->setText(info["name"].toString());
}

