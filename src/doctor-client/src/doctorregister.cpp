#include "doctorregister.h"
#include "doctorlogin.h"
#include "ui_doctorregister.h"
#include <regex>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

DoctorRegister::DoctorRegister(QWidget *parent, RpcClient *rClient, CredentialManager *cR) :
    QWidget(parent),
    ui(new Ui::DoctorRegister), doctorCredential(cR), requestSender(rClient)
{
    ui->setupUi(this);
}

DoctorRegister::~DoctorRegister()
{
    delete ui;
}

bool DoctorRegister::checkName() {
    return ui->dname->text().length() >= 2 && ui->dname->text().length() <= 10;
}

bool DoctorRegister::checkIdCard() {
    QString txt = ui->did->text();
    int len = txt.length();
    if(len != 18) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && (i != len - 1 || txt[i] != 'X')) return false;
    }
    return true;
}

bool DoctorRegister::checkPassword(){
    QString txt = ui->password->text();
    int len = txt.length();
    if(len < 7 || len > 20) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && !txt[i].isLower() && !txt[i].isUpper()) return false;
    }
    return true;
}

void DoctorRegister::on_register_2_clicked() {

    if (!checkName()) {
        QMessageBox::warning(this, "Warning", "Invalid name!");
        return;
    }
    if (!checkPassword()) {
        QMessageBox::warning(this, "Warning", "Ur password must be between 7 and 20 characters and shall not contain characters except numbers and upper or lower letters.");
        return;
    }
    if (ui->checkpass->text() != ui->password->text())  {
        QMessageBox::warning(this, "Warning", "Check ur password again!");
        return;
    }
    if (!checkIdCard()) {
        QMessageBox::warning(this, "Warning", "Invalid ID, check your ID or turn to database manager.");
        return;
    }

    QJsonObject registerData;
    registerData["name"] = ui->dname->text();
    registerData["idCard"] = ui->did->text();
    registerData["password"] = ui->password->text();

    Response result = requestSender->rpc(Request("doctor.register", doctorCredential->get(), registerData));
    qDebug() << result.data;

    if(!result.success) {
        QMessageBox::warning(this, "警告！", "您已注册过账号！");
        return;
    }
    QMessageBox::information(this, "Congratulations!", "注册成功！将在3秒后返回登录界面。");
    loginBoard->show();
    this->hide();
    return;
}
