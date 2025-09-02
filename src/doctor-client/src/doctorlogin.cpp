#include "doctorlogin.h"
#include "ui_doctorlogin.h"
#include "doctorregister.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <memory>
#include <QDebug>

DoctorLogin::DoctorLogin(QWidget *parent, RpcClient *rClient, CredentialManager *cR)
    : QMainWindow(parent)
    , ui(new Ui::DoctorLogin), doctorCredential(cR), requestSender(rClient)
{
    registerBoard = nullptr;
    doctorBoard = nullptr;
    ui->setupUi(this);
    ui->loginBtn->setObjectName("okBtn");
    ui->label_3->setObjectName("titleLabel");
}

DoctorLogin::~DoctorLogin()
{
    delete ui;
}

bool DoctorLogin::checkUsername() {
    QString txt = ui->username->text();
    int len = txt.length();
    if (len != 18) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && (i != len - 1 || txt[i] != 'X')) return false;
    }
    return true;
}

bool DoctorLogin::checkPassword() {
    QString txt = ui->password->text();
    int len = txt.length();
    if(len < 7 || len > 20) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && !txt[i].isLower() && !txt[i].isUpper()) return false;
    }
    return true;
}

void DoctorLogin::on_loginBtn_clicked()
{
    if(ui->username->text() == "" || ui->password->text() == "") {
        QMessageBox::warning(this, "提示", "用户名或密码不能为空。");
        return;
    }
    else if(!checkUsername() || !checkPassword()) {
        QMessageBox::warning(this, "提示", "请检查你的用户名或密码格式。");
        return;
    }
    QJsonObject loginData;
    loginData["idCard"] = ui->username->text();
    loginData["password"] = ui->password->text();
    Response result = requestSender->rpc(Request("doctor.login", doctorCredential->get(), loginData));
    qDebug() << result.data;
//    bool flag = false;
    if(!result.success) {
        QMessageBox::warning(this, "提示", "用户名不存在或密码错误。");
    }
    else {
        doctorCredential->set(Credential::parse(result.data["credential"].toString()));
        if(!doctorBoard) doctorBoard = std::make_unique<Doctor>(nullptr, requestSender, doctorCredential);
        emit loginSucceed(ui->username->text());
        doctorBoard->setMinimumSize(1600, 900);
        doctorBoard -> show();
        this -> hide();
    }
}

void DoctorLogin::on_registerBtn_clicked()
{
    if(!registerBoard) registerBoard = std::make_unique<DoctorRegister>();
    registerBoard -> show();
    registerBoard -> setLoginBoard(this);
    this -> hide();
}
