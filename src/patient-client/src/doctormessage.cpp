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
    ui->content->setObjectName("otherMessage");
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
    // 先测真实内容宽度
    QFontMetrics fm(ui->content->font());
    int contentWidth = fm.horizontalAdvance(ui->content->toPlainText());
    qreal maxWidth = fatherWindow->width() * 0.7;
    qreal finalWidth = qMin(qreal(contentWidth + 30), maxWidth);

    if(qreal(contentWidth) > maxWidth) {
        ui->content->document()->setTextWidth(finalWidth);
    }
    else{
        ui->content->document()->setTextWidth(-1);
    }
    ui->content->setMaximumWidth(finalWidth + 60);
    ui->content->setMaximumHeight(ui->content->document()->size().height());
    this->resize(ui->content->size());
    ui->content->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->content->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
