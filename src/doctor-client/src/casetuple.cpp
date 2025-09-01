#include "casetuple.h"
#include "ui_casetuple.h"

CaseTuple::CaseTuple(QString name, QString id, QString diagnosis, QString prescription, QString advice, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaseTuple)
{
    ui->setupUi(this);
    fatherMainWindow = nullptr;
//    ui->m_patientName->setReadOnly(true);
//    ui->m_patientId->setReadOnly(true);
    ui->m_diagnosis->setReadOnly(true);
    ui->m_prescription->setReadOnly(true);
    ui->m_advice->setReadOnly(true);
//    ui->m_patientName->setText(name);
//    ui->m_patientId->setText(id);
    ui->m_diagnosis->setText(diagnosis);
    ui->m_prescription->setText(prescription);
    ui->m_advice->setText(advice);
}

CaseTuple::~CaseTuple()
{
    delete ui;
}
