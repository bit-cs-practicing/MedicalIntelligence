#include "casedatabrief.h"
#include "casedatadetails.h"
#include "mainwindow.h"
#include "ui_casedatabrief.h"

#include <QDate>
#include <QJsonObject>

CaseDataBrief::CaseDataBrief(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaseDataBrief)
{
    ui->setupUi(this);
    ui->caseId->setReadOnly(true);
    ui->caseDateTime->setEnabled(false);
}

CaseDataBrief::~CaseDataBrief() {
    delete ui;
}

void CaseDataBrief::setCaseInfo(QString caseId, QString date) {
    ui->caseDateTime->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    ui->caseId->setText(caseId);
}

void CaseDataBrief::on_details_clicked() {
    CaseDataDetails *caseDetails = new CaseDataDetails;
    QJsonObject details = fatherMainWindow->queryByCaseId(ui->caseId->text());
    caseDetails->setCaseDataDetails(details);
    caseDetails->show();
}
