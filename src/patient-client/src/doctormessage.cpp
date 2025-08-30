#include "doctormessage.h"
#include "topicdatadetails.h"
#include "ui_doctormessage.h"
#include <QDebug>
#include <QTextBlock>
#include <QRectF>
#include <QAbstractTextDocumentLayout>
DoctorMessage::DoctorMessage(QWidget *parent, TopicDataDetails *father) :
    QWidget(parent),
    ui(new Ui::DoctorMessage), fatherWindow(father)
{
    ui->setupUi(this);
    ui->content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->name->setReadOnly(true);
    adjustTextBrowserHeight();
}

DoctorMessage::~DoctorMessage()
{
    delete ui;
}

void DoctorMessage::setDoctorMessage(QString name, QString content) {
    ui->name->setText(name), ui->content->setText(content);
    adjustTextBrowserHeight();
}
void DoctorMessage::adjustTextBrowserHeight() {
    ui->content->document()->setTextWidth(fatherWindow->width() * 0.7);
    ui->content->setFixedHeight(ui->content->document()->size().height());
    ui->content->setFixedWidth(ui->content->document()->size().width());
    this->resize(ui->content->size());
}
