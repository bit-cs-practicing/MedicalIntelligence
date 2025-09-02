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
    ui->content->setFixedWidth(finalWidth);
    ui->content->setFixedHeight(ui->content->document()->size().height());
    this->resize(ui->content->size());

    qDebug() << "finalWidth:" << finalWidth << " size:" << ui->content->size();
}
void PatientMessage::setTextEnabled(bool flag) {
    ui->content->setEnabled(flag);
}
