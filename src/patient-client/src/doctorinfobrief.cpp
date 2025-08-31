#include "doctorinfobrief.h"
#include "ui_doctorinfobrief.h"
#include "mainwindow.h"
#include "doctorinfodetails.h"
#include "patientappointment.h"
#include <QJsonObject>
#include <QDebug>
DoctorInfoBrief::DoctorInfoBrief(QWidget *parent, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::DoctorInfoBrief), patientCredential(pC), requestSender(rSender)
{
    fatherMainWindow = nullptr;
    ui->setupUi(this);
    ui->name->setReadOnly(true);
    ui->office->setReadOnly(true);
    ui->doctorID->setReadOnly(true);
}

DoctorInfoBrief::~DoctorInfoBrief()
{
    delete ui;
}

void DoctorInfoBrief::setDoctorBriefInfo(QString ID, QString name, QString depart) {
    ui->name->setText(name);
    ui->doctorID->setText(ID);
    ui->office->setText(depart);
}

void DoctorInfoBrief::on_details_clicked()
{
//    qDebug() << "start\n";
    QJsonObject details = fatherMainWindow->queryByDoctorId(ui->doctorID->text());
//    qDebug() << details << "\n";
    DoctorInfoDetails *newDetails = new DoctorInfoDetails;
    newDetails->setInformations(details);
    newDetails->show();
}

void DoctorInfoBrief::on_pushButton_clicked()
{
    PatientAppointment *newAppointment = new PatientAppointment(nullptr, requestSender, patientCredential);
    newAppointment->setDoctorInformation(ui->name->text(), ui->doctorID->text());
    newAppointment->show();
}
