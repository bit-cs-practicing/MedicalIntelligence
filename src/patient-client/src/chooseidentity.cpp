#include "chooseidentity.h"
#include "ui_chooseidentity.h"

ChooseIdentity::ChooseIdentity(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChooseIdentity)
{
    loginBoard = nullptr;
    ui->setupUi(this);
}

ChooseIdentity::~ChooseIdentity()
{
    delete ui;
}


void ChooseIdentity::on_Patient_clicked()
{
    if(!loginBoard)
        loginBoard = std::make_unique<PatientLogin>();
    loginBoard -> show();
    this -> hide();
}
