#include "patientmessage.h"
#include "ui_patientmessage.h"
#include "topicdatadetails.h"

PatientMessage::PatientMessage(QWidget *parent, TopicDataDetails *father) :
    QWidget(parent),
    ui(new Ui::PatientMessage), fatherWindow(father)
{
    ui->setupUi(this);
    ui->name->setReadOnly(true);
    ui->content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    adjustTextBrowserHeight();
}

PatientMessage::~PatientMessage()
{
    delete ui;
}

void PatientMessage::setPatientMessage(QString name, QString content) {
    ui->name->setText(name), ui->content->setText(content);
    adjustTextBrowserHeight();
}
void PatientMessage::adjustTextBrowserHeight() {
    ui->content->document()->setTextWidth(fatherWindow->width() * 0.7);
    ui->content->setFixedHeight(ui->content->document()->size().height());
    ui->content->setFixedWidth(ui->content->document()->size().width());
    this->resize(ui->content->size());
}
void PatientMessage::setTextEnabled(bool flag) {
    ui->content->setEnabled(flag);
}
