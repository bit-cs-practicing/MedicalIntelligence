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
    ui->registerBtn->setObjectName("okBtn");
    ui->returnBtn->setObjectName("criticalBtn");
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
        QMessageBox::warning(this, "提示", "姓名非法!");
        return;
    }
    if (!checkPassword()) {
        QMessageBox::warning(this, "提示", "密码必须为 7 到 20 位的字符，且只能包含大小写字母与数字。");
        return;
    }
    if (ui->checkpass->text() != ui->password->text())  {
        QMessageBox::warning(this, "提示", "请检查你的密码");
        return;
    }
    if (!checkIdCard()) {
        QMessageBox::warning(this, "提示", "用户名无效，请检查你的用户名或联系数据库管理员。");
        return;
    }

    QJsonObject registerData;
    registerData["name"] = ui->dname->text();
    registerData["idCard"] = ui->did->text();
    registerData["password"] = ui->password->text();

    Response result = requestSender->rpc(Request("doctor.register", doctorCredential->get(), registerData));
    qDebug() << result.data;

    if(!result.success) {
        QMessageBox::warning(this, "提示", "您已注册过账号！");
        return;
    }
    QMessageBox::information(this, "提示", "注册成功！将在3秒后返回登录界面。");
    loginBoard->show();
    this->hide();
    return;
}

void DoctorRegister::on_returnBtn_clicked() {
    loginBoard->show();
    this->hide();
}
