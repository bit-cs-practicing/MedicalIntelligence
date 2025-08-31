#include "casedatadetails.h"
#include "ui_casedatadetails.h"
#include <QJsonObject>
#include <QDate>
CaseDataDetails::CaseDataDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaseDataDetails)
{
    ui->setupUi(this);
    ui->caseId->setReadOnly(true);
    ui->date->setReadOnly(true);
    ui->diagnosis->setReadOnly(true);
    ui->prescription->setReadOnly(true);
    ui->advice->setReadOnly(true);
}

CaseDataDetails::~CaseDataDetails()
{
    delete ui;
}

void CaseDataDetails::setCaseDataDetails(QJsonObject q) {
    ui->caseId->setText(q["caseId"].toString());
    ui->date->setDate(QDate::fromString(q["visitDate"].toString(), "yyyy-MM-dd"));
    ui->diagnosis->setText(q["diagnosis"].toString());
    ui->prescription->setText(q["prescription"].toString());
    ui->advice->setText(q["advice"].toString());
}
