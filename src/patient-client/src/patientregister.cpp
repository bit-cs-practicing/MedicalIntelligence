#include "patientregister.h"
#include "ui_patientregister.h"
#include <regex>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include "patientlogin.h"
#include <QThread>
PatientRegister::PatientRegister(QWidget *parent, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::PatientRegister), patientCredential(pC), requestSender(rSender)
{
    ui->setupUi(this);
    ui->register_2->setObjectName("okBtn");
}

PatientRegister::~PatientRegister()
{
    delete ui;
}

bool PatientRegister::checkName() {
    return ui->name->text().length() >= 2 && ui->name->text().length() <= 10;
}

bool PatientRegister::checkIdCard() {
    QString txt = ui->idCard->text();
    int len = txt.length();
    if(len != 18) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && (i != len - 1 || txt[i] != 'X')) return false;
    }
    return true;
}

bool PatientRegister::checkPassword(){
    QString txt = ui->password->text();
    int len = txt.length();
    if(len < 7 || len > 20) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && !txt[i].isLower() && !txt[i].isUpper()) return false;
    }
    return true;
}

bool PatientRegister::checkPhone(QString S){
    if(S.length() != 11) return false;
    if(S[0] != '1') return false;
    for(int i = 1; i < 11; ++i)
        if(!S[i].isDigit()) return false;
    return true;
}

bool PatientRegister::checkEmail(){
    const std::regex emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(ui->email->text().toStdString(), emailRegex);
}



void PatientRegister::on_register_2_clicked()
{
    if(!checkName()) {
        QMessageBox::warning(this, "警告！", "请输入真实姓名！");
        return;
    }
    else if(!checkIdCard()) {
        QMessageBox::warning(this, "警告！", "身份证号错误！");
        return;
    }
    else if(!checkEmail()) {
        QMessageBox::warning(this, "警告！", "请输入合法的邮箱！");
        return;
    }
    else if(!checkPassword()) {
        QMessageBox::warning(this, "警告！", "请输入7到20位密码，密码只应包含数字、大小写字母！");
        return;
    }
    else if(ui->password->text() != ui->checkpass->text()){
        QMessageBox::warning(this, "警告！", "两次输入的密码不一致！");
        return;
    }
    else if(!checkPhone(ui->phone->text())) {
        QMessageBox::warning(this, "警告！", "请输入合法的电话号码！");
        return;
    }
    else if(!checkPhone(ui->emgcy->text())) {
        QMessageBox::warning(this, "警告！", "请输入合法的紧急联系人电话！");
        return;
    }
    QJsonObject registerData;
    registerData["name"] = ui->name->text();
    registerData["password"] = ui->password->text();
    registerData["gender"] = ui->gender->currentText();
//    qDebug() << registerData["gender"] << "\n";
    registerData["idCard"] = ui->idCard->text();
    registerData["phone"] = ui->phone->text();
    registerData["birthday"] = ui->birthday->date().toString("yyyy-MM-dd");
//    qDebug() << registerData["birthday"] << "\n";
    registerData["email"] = ui->email->text();
    registerData["emergencyContact"] = ui->emgcy->text();
    Response result = requestSender->rpc(Request("patient.register", patientCredential->get(), registerData));
    qDebug() << result.data << "\n";
    if(!result.success) {
        QMessageBox::warning(this, "警告！", "您已注册过账号！");
        return;
    }
    else{
        QMessageBox::information(this, "恭喜!", "注册成功！将在3秒后返回登录界面。");
        QThread::sleep(3);
        loginBoard -> show();
        this -> hide();
    }
}

void PatientRegister::on_returnBtn_clicked()
{
    loginBoard -> show();
    this -> hide();
}
