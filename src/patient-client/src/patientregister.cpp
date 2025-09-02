#include "patientregister.h"
#include "ui_patientregister.h"
#include "patientlogin.h"
#include "util.h"

#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QThread>
PatientRegister::PatientRegister(QWidget *parent, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::PatientRegister), patientCredential(pC), requestSender(rSender)
{
    ui->setupUi(this);
    ui->register_2->setObjectName("okBtn");
}

PatientRegister::~PatientRegister() {
    delete ui;
}

void PatientRegister::on_register_2_clicked()
{
    if (!Util::checkName(ui->name->text())) {
        QMessageBox::warning(this, "警告！", "请输入真实姓名！");
        return;
    }
    if (!Util::checkIdCard(ui->idCard->text())) {
        QMessageBox::warning(this, "警告！", "身份证号错误！");
        return;
    }
    if (!Util::checkEmail(ui->email->text().toStdString())) {
        QMessageBox::warning(this, "警告！", "请输入合法的邮箱！");
        return;
    }
    if (!Util::checkPassword(ui->password->text())) {
        QMessageBox::warning(this, "警告！", "请输入7到20位密码，密码只应包含数字、大小写字母！");
        return;
    }
    if (ui->password->text() != ui->checkpass->text()){
        QMessageBox::warning(this, "警告！", "两次输入的密码不一致！");
        return;
    }
    if (!Util::checkPhone(ui->phone->text())) {
        QMessageBox::warning(this, "警告！", "请输入合法的电话号码！");
        return;
    }
    if (!Util::checkPhone(ui->emgcy->text())) {
        QMessageBox::warning(this, "警告！", "请输入合法的紧急联系人电话！");
        return;
    }
    QJsonObject registerData;
    registerData["name"] = ui->name->text();
    registerData["password"] = ui->password->text();
    registerData["gender"] = Util::transferGenderFromZHToEN(ui->gender->currentText());
    registerData["idCard"] = ui->idCard->text();
    registerData["phone"] = ui->phone->text();
    registerData["birthday"] = ui->birthday->date().toString("yyyy-MM-dd");
    registerData["email"] = ui->email->text();
    registerData["emergencyContact"] = ui->emgcy->text();
    Response result = requestSender->rpc(Request("patient.register", patientCredential->get(), registerData));
    qDebug() << result.data << "\n";
    if (!result.success) {
        QMessageBox::warning(this, "警告！", "您已注册过账号！");
        return;
    } else {
        QMessageBox::information(this, "恭喜!", "注册成功！将在3秒后返回登录界面。");
        QThread::sleep(3);
        loginBoard -> show();
        this -> hide();
    }
}

void PatientRegister::on_returnBtn_clicked() {
    loginBoard -> show();
    this -> hide();
}
