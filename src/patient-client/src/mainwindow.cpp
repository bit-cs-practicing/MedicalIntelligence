#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "doctorinfobrief.h"
#include "appointmentdata.h"
#include "topicdatabrief.h"
#include "casedatabrief.h"
#include <algorithm>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <regex>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    doctorInformations.clear();
    ui->Tabs->setCurrentIndex(0);
    ui->appTimeComboBox->setCurrentText("All times");
    ui->caseComboBox->setCurrentText("所有时间");
    ui->caseDateTime->setEnabled(false);
    ui->appListDate->setEnabled(false);
    ui->appListDate->setDate(QDate::currentDate());
    ui->caseDateTime->setDate(QDate::currentDate());
    ui->topicComboBox->setCurrentText("按话题Id排序");
    connect(ui->appTimeComboBox, &QComboBox::currentTextChanged, this, [&](const QString &S){
        if(S == "All times") ui->appListDate->setEnabled(false);
        else ui->appListDate->setEnabled(true);
    });
    connect(ui->caseComboBox, &QComboBox::currentTextChanged, this, [&](const QString &S){
        if(S == "所有时间") ui->caseDateTime->setEnabled(false);
        else ui->caseDateTime->setEnabled(true);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAppListComboBox() {
    QStringList S = {"All Doctors"}, S2 = {"All times", "Specific time"};
    for(QJsonObject i : appointmentInformations) {
        if(!S.contains(i["doctorId"].toString())) S.append(i["doctorId"].toString());
    }
    ui->appListComboBox->clear();
    ui->appListComboBox->addItems(S);
}

void MainWindow::loadCaseInfo() {
    caseInformations.clear();
    QJsonObject caseData;
    caseData["caseId"] = QString("C10001"), caseData["visitDate"] = QString("2025-08-31");
    caseData["diagnosis"] = QString("感冒"), caseData["prescription"] = QString("每天喝一吨热水。");
    caseData["advice"] = QString("多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~");
    caseInformations.append(caseData);

    caseData["caseId"] = QString("C10002"), caseData["visitDate"] = QString("2025-08-31");
    caseData["diagnosis"] = QString("感冒"), caseData["prescription"] = QString("每天喝一吨热水。");
    caseData["advice"] = QString("多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~");
    caseInformations.append(caseData);

    caseData["caseId"] = QString("C10003"), caseData["visitDate"] = QString("2025-08-30");
    caseData["diagnosis"] = QString("感冒"), caseData["prescription"] = QString("每天喝一吨热水。");
    caseData["advice"] = QString("多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~多喝热水~");
    caseInformations.append(caseData);

    showCaseInfo("所有时间");
}

void MainWindow::sortTopicById() {
    std::sort(topicInformations.begin(), topicInformations.end(), [](const QJsonObject &A, const QJsonObject &B){
        return A["topicId"].toString() > B["topicId"].toString();
    });
}

void MainWindow::sortTopicByTime() {
    std::sort(topicInformations.begin(), topicInformations.end(), [](const QJsonObject &A, const QJsonObject &B){
        return A["lastMessageTime"].toString() > B["lastMessageTime"].toString();
    });
}

void MainWindow::loadTopicInfo() {
    topicInformations.clear();
    QJsonObject topicData;
    topicData["topicId"] = "T1000000", topicData["lastMessageTime"] = "2025-01-03T10:00:00";
    topicInformations.append(topicData);
    topicData["topicId"] = "T1000001", topicData["lastMessageTime"] = "2025-01-03T08:00:00";
    topicInformations.append(topicData);
    topicData["topicId"] = "T1000002", topicData["lastMessageTime"] = "2025-01-03T09:00:00";
    topicInformations.append(topicData);

    showTopicInfo("");
}

void MainWindow::loadAppointmentInfo() {
    appointmentInformations.clear();
    QJsonObject appointmentData;
    appointmentData["appointmentId"] = QString("A10000"), appointmentData["doctorId"] = QString("D0001");
    appointmentData["date"] = QString("2025-09-01"), appointmentData["timeSlot"] = QString("09:00-09:29");
    appointmentData["status"] = "scheduled";
    appointmentInformations.append(appointmentData);

    appointmentData["appointmentId"] = QString("A10001"), appointmentData["doctorId"] = QString("D0001");
    appointmentData["date"] = QString("2025-09-01"), appointmentData["timeSlot"] = QString("10:00-10:29");
    appointmentData["status"] = "cancelled";
    appointmentInformations.append(appointmentData);

    appointmentData["appointmentId"] = QString("A10003"), appointmentData["doctorId"] = QString("D0002");
    appointmentData["date"] = QString("2025-08-31"), appointmentData["timeSlot"] = QString("09:00-09:29");
    appointmentData["status"] = "completed";
    appointmentInformations.append(appointmentData);

    setAppListComboBox();
    showAppointmentInfo("All Doctors", "All times");
}

void MainWindow::loadInformation(){
    QJsonObject registerData;
    registerData["name"] = QString("wxy"), registerData["idCard"] = QString("123456789012345678");
    registerData["gender"] = QString("male"), registerData["email"] = QString("12345@126.com");
    registerData["phone"] = QString("12345678901"), registerData["emergencyContact"] = QString("12345678901");
    registerData["birthday"] = QString("2005-01-19"), registerData["patientId"] = QString("P0001");
    ui->name->setText(registerData["name"].toString());
    ui->idCard->setText(registerData["idCard"].toString());
    ui->gender->setCurrentText(registerData["gender"].toString());
    ui->email->setText(registerData["email"].toString());
    ui->phone->setText(registerData["phone"].toString());
    ui->emgcy->setText(registerData["emergencyContact"].toString());
    ui->birthday->setDate(QDate::fromString(registerData["birthday"].toString(), "yyyy-MM-dd"));
    ui->name->setEnabled(false);
    ui->idCard->setEnabled(false);
    ui->gender->setEnabled(false);
    ui->birthday->setEnabled(false);
    patientId = registerData["patientId"].toString();
}

void MainWindow::showDoctorInfo(QString depart) {
    QWidget *scrollContent = new QWidget(this); // 滚动区域的内容容器
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent); // 容器的布局
    scrollContent->setLayout(scrollLayout);
    for(QJsonObject i : doctorInformations) {
        if(i["department"].toString() == depart || depart == "All") {
            DoctorInfoBrief *p = new DoctorInfoBrief(scrollContent);
            p->setDoctorBriefInfo(i["employeeId"].toString(), i["name"].toString(), i["department"].toString());
            p->setFatherMainWindow(this);
            scrollLayout->addWidget(p);
        }
    }
    ui->docInfoScreen->setWidget(scrollContent);
    ui->docInfoScreen->setWidgetResizable(true); // 确保内容自适应滚动区域
}

void MainWindow::showAppointmentInfo(QString doctorId, QString dateTime) {
    QWidget *scrollContent = new QWidget(this);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(scrollLayout);
    for(QJsonObject i : appointmentInformations) {
        if((i["doctorId"].toString() == doctorId || doctorId == "All Doctors") && (i["date"].toString() == dateTime || dateTime == "All times")) {
            AppointmentData *p = new AppointmentData(scrollContent);
            p->setAppointmentData(i["appointmentId"].toString(), i["doctorId"].toString(), i["date"].toString(), i["timeSlot"].toString(), i["status"].toString());
            scrollLayout->addWidget(p);
        }
    }
    ui->appListScreen->setWidget(scrollContent);
    ui->appListScreen->setWidgetResizable(true);
}

void MainWindow::showCaseInfo(QString date) {
    QWidget *scrollContent = new QWidget(this);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(scrollLayout);
    for(QJsonObject i : caseInformations) {
        if(i["visitDate"].toString() == date || date == "所有时间") {
            CaseDataBrief *p = new CaseDataBrief(scrollContent);
            p->setCaseInfo(i["caseId"].toString(), i["visitDate"].toString());
            p->setFatherMainWindow(this);
            scrollLayout->addWidget(p);
        }
    }
    ui->caseScreen->setWidget(scrollContent);
    ui->caseScreen->setWidgetResizable(true);
}

void MainWindow::showTopicInfo(QString S) {
    if(ui->topicComboBox->currentText() == "按话题Id排序") sortTopicById();
    else sortTopicByTime();
    QWidget *scrollContent = new QWidget(this);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(scrollLayout);
    for(QJsonObject i : topicInformations) {
        if(i["topicId"] == S || S == "") {
            TopicDataBrief *p = new TopicDataBrief(scrollContent, patientId);
            p->setTopicInfo(i["topicId"].toString(), i["lastMessageTime"].toString());
            p->setParent(this);
            scrollLayout->addWidget(p);
//            p->deleteLater();
        }
    }
    ui->topicScreen->setWidget(scrollContent);
    ui->topicScreen->setWidgetResizable(true);
}

void MainWindow::setDoctorInfoComboBox() {
    QStringList S = {"All"};
    for(QJsonObject i : doctorInformations) {
        QString tmp = i["department"].toString();
        if(!S.contains(tmp)) S.append(tmp);
    }
//    qDebug << S << "\n";
    ui->docInfoCOffice->clear();
//    qDebug() << "adding Items\n";
    ui->docInfoCOffice->addItems(S);
}

void MainWindow::loadDoctorInfo() {
    doctorInformations.clear();
    QJsonObject Doctor;
    Doctor["employeeId"] = QString("D00001"), Doctor["department"] = QString("Office1");
    Doctor["profile"] = QString("I am Docotr1"), Doctor["photo"] = QString("Photo1");
    Doctor["workSchedule"] = QString("all days"), Doctor["registrationFee"] = QString("50");
    Doctor["dailyPatientLimit"] = QString("30"), Doctor["name"] = QString("Doctor1");
    doctorInformations.append(Doctor);

    Doctor["employeeId"] = QString("D00002"), Doctor["department"] = QString("Office1");
    Doctor["profile"] = QString("I am Docotr2"), Doctor["photo"] = QString("Photo1");
    Doctor["workSchedule"] = QString("all days"), Doctor["registrationFee"] = QString("50");
    Doctor["dailyPatientLimit"] = QString("30"), Doctor["name"] = QString("Doctor2");
    doctorInformations.append(Doctor);

    Doctor["employeeId"] = QString("D00003"), Doctor["department"] = QString("Office2");
    Doctor["profile"] = QString("I am Docotr3"), Doctor["photo"] = QString("Photo1");
    Doctor["workSchedule"] = QString("all days"), Doctor["registrationFee"] = QString("50");
    Doctor["dailyPatientLimit"] = QString("30"), Doctor["name"] = QString("Doctor3");
    doctorInformations.append(Doctor);

    setDoctorInfoComboBox();
    showDoctorInfo("All");
}

QJsonObject MainWindow::queryByDoctorId(QString Id) {
    for(QJsonObject i : doctorInformations) {
        if(i["employeeId"].toString() == Id) return i;
    }
    exit(-1);
}

QJsonObject MainWindow::queryByCaseId(QString Id) {
    for(QJsonObject i : caseInformations) {
        if(i["caseId"].toString() == Id) return i;
    }
    exit(-1);
}

void MainWindow::on_Tabs_tabBarClicked(int index)
{
    if(index == 0) {
        loadInformation();
    }
    else if(index == 2) {
        loadDoctorInfo();
    }
    else if(index == 3) {
        loadAppointmentInfo();
    }
    else if(index == 4) {
        loadCaseInfo();
    }
    else if(index == 5) {
        loadTopicInfo();
    }
}
bool MainWindow::checkPhone(QString S){
    if(S.length() != 11) return false;
    if(S[0] != '1') return false;
    for(int i = 1; i < 11; ++i)
        if(!S[i].isDigit()) return false;
    return true;
}
bool MainWindow::checkEmail(){
    const std::regex emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(ui->email->text().toStdString(), emailRegex);
}

bool MainWindow::checkPassword(QString txt){
    int len = txt.length();
    if(len < 7 || len > 20) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && !txt[i].isLower() && !txt[i].isUpper()) return false;
    }
    return true;
}

void MainWindow::on_changeinfoBtn_clicked()
{
    if(!checkEmail()) {
        QMessageBox::warning(this, "警告！", "请输入合法的邮箱！");
        return;
    }
    else if(!checkPhone(ui->phone->text())){
        QMessageBox::warning(this, "警告！", "请输入合法的电话号码！");
        return;
    }
    else if(!checkPhone(ui->emgcy->text())) {
        QMessageBox::warning(this, "警告！", "请输入合法的紧急联系人电话！");
        return;
    }
    QJsonObject registerData;
    registerData["name"] = ui->name->text();
    registerData["gender"] = ui->gender->currentText();
    registerData["phone"] = ui->phone->text();
    registerData["birthday"] = ui->birthday->date().toString("yyyy-MM-dd");
    registerData["email"] = ui->email->text();
    registerData["emergencyContact"] = ui->emgcy->text();
    bool flag = true;
    if(flag) QMessageBox::information(this, "Congratulations!", "个人信息更新成功！");
    else QMessageBox::warning(this, "警告！", "请重新提交表单！");
}

void MainWindow::on_updPassBtn_clicked()
{
    if(!checkPassword(ui->oldpass->text())){
        QMessageBox::warning(this, "警告！", "旧密码错误！");
        return;
    }
    else if(!checkPassword(ui->newpass->text())) {
        QMessageBox::warning(this, "警告！", "请输入合法的新密码！密码长度为7至20位，只由数字、大小写字母组成！");
        return;
    }
    QJsonObject changePassData;
    changePassData["oldPassword"] = ui->oldpass->text();
    changePassData["newPassword"] = ui->newpass->text();
    bool flag = true;
    if(flag) QMessageBox::information(this, "Congratulations!", "更改密码成功！");
    else QMessageBox::warning(this, "警告！", "旧密码错误！");
}

void MainWindow::on_docInfoCheck_clicked()
{
    showDoctorInfo(ui->docInfoCOffice->currentText());
}

void MainWindow::on_appListCheck_clicked()
{
    QString doctorId = ui->appListComboBox->currentText(), date = ui->appTimeComboBox->currentText();
    if(date != "All times") date = ui->appListDate->date().toString("yyyy-MM-dd");
//    qDebug() << doctorId << " " << date << "\n";
    showAppointmentInfo(doctorId, date);
}

void MainWindow::on_caseCheckBtn_clicked()
{
    QString date;
    if(ui->caseComboBox->currentText() == "所有时间") date = "所有时间";
    else date = ui->caseDateTime->date().toString("yyyy-MM-dd");
    showCaseInfo(date);
}

void MainWindow::on_topicCheckBtn_clicked()
{
    showTopicInfo(ui->topicEnter->text());
}
