#include "pmessage.h"
#include "ui_pmessage.h"
#include <QWidget>

pMessage::pMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pMessage)
{
    ui->setupUi(this);
    ui->pName->setReadOnly(true);
    ui->pMessageContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    //adjustTextBrowserHeight();
}

pMessage::~pMessage()
{
    delete ui;
}

/*void pMessage::adjustTextBrowserHeight() {
    ui->pMessageContent->document()->setTextWidth(fatherWindow->width() * 0.7);
    ui->pMessageContent->setFixedHeight(ui->content->document()->size().height());
    ui->pMessageContent->setFixedWidth(ui->content->document()->size().width());
    this->resize(ui->pMessageContent->size());
}
*/
