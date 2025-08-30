#include "patientlogin.h"
#include "ui_patientlogin.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <memory>
PatientLogin::PatientLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientLogin)
{
    registerBoard = nullptr;
    patientWindow = nullptr;
    ui->setupUi(this);
}

PatientLogin::~PatientLogin()
{
    delete ui;
}

bool PatientLogin::checkUsername(){
    QString txt = ui->username->text();
    int len = txt.length();
    if(len != 18) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && (i != len - 1 || txt[i] != 'X')) return false;
    }
    return true;
}

bool PatientLogin::checkPassword(){
    QString txt = ui->password->text();
    int len = txt.length();
    if(len < 7 || len > 20) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && !txt[i].isLower() && !txt[i].isUpper()) return false;
    }
    return true;
}

void PatientLogin::on_loginBtn_clicked()
{
    if(ui->username->text() == "" || ui->password->text() == "") {
        QMessageBox::warning(this, "警告！", "用户名和密码不能为空！");
        return;
    }
    else if(!checkUsername() || !checkPassword()) {
        QMessageBox::warning(this, "警告！", "用户不存在或密码错误！");
        return;
    }
    QJsonObject loginData;
    loginData["idCard"] = ui->username->text();
    loginData["password"] = ui->password->text();
    bool flag = true;
    if(!flag) {
        QMessageBox::warning(this, "警告！", "用户不存在或密码错误！");
    }
    else{
        QMessageBox::information(this, "Congratulations!", "登录成功！");
        if(!patientWindow) patientWindow = std::make_unique<MainWindow>();
        patientWindow->loadInformation();
        patientWindow->show();
        this->hide();
    }
}

void PatientLogin::on_registerBtn_clicked()
{
    if(!registerBoard) registerBoard = std::make_unique<PatientRegister>();
    registerBoard -> show();
    registerBoard -> setLoginBoard(this);
    this -> hide();
}
