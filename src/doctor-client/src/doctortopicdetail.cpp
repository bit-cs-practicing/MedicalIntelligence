#include "doctortopicdetail.h"
#include "ui_doctortopicdetail.h"

doctorTopicDetail::doctorTopicDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctorTopicDetail)
{
    ui->setupUi(this);
}

doctorTopicDetail::~doctorTopicDetail()
{
    delete ui;
}
