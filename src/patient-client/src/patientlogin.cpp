#include "patientlogin.h"
#include "ui_patientlogin.h"
#include "util.h"

#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <memory>
PatientLogin::PatientLogin(QWidget *parent, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::PatientLogin), patientCredential(pC), requestSender(rSender)
{
    registerBoard = nullptr;
    patientWindow = nullptr;
    ui->setupUi(this);
    ui->loginBtn->setObjectName("okBtn");
    ui->title->setObjectName("titleLabel");
}

PatientLogin::~PatientLogin() {
    delete ui;
}

void PatientLogin::on_loginBtn_clicked()
{
    const QString username = ui->username->text();
    const QString password = ui->password->text();
    if(username == "" || password == "") {
        QMessageBox::warning(this, "警告！", "用户名和密码不能为空！");
        return;
    }
    else if(!Util::checkIdCard(username) || !Util::checkPassword(password)) {
        QMessageBox::warning(this, "警告！", "用户不存在或密码错误！");
        return;
    }
    QJsonObject loginData;
    loginData["idCard"] = username;
    loginData["password"] = password;
    Response result = requestSender->rpc(Request("patient.login", patientCredential->get(), loginData));
    qDebug() << result.toStream() << "\n";
    if(!result.success) {
        QMessageBox::warning(this, "警告！", "用户不存在或密码错误！");
    }
    else{
        patientCredential->set(Credential::parse(result.data["credential"].toString()));
        QMessageBox::information(this, "恭喜!", "登录成功！");
        if(!patientWindow) patientWindow = std::make_unique<MainWindow>(nullptr, requestSender, patientCredential);
        patientWindow->loadInformation();
        patientWindow->setMinimumSize(1600, 900);
        patientWindow->show();
        this->hide();
    }
}

void PatientLogin::on_registerBtn_clicked()
{
    if(!registerBoard) registerBoard = std::make_unique<PatientRegister>(nullptr, requestSender, patientCredential);
    registerBoard -> show();
    registerBoard -> setLoginBoard(this);
    this -> hide();
}
