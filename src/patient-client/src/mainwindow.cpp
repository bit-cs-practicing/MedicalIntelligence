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
MainWindow::MainWindow(QWidget *parent, RpcClient *rSender, CredentialManager *pC) :
    QWidget(parent),
    ui(new Ui::MainWindow), patientCredential(pC), requestSender(rSender)
{
    ui->setupUi(this);
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
    loadDoctorInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAppListComboBox() {
    QStringList S = {"All Doctors"}, S2 = {"All times", "Specific time"};
    for(QJsonValue i : appointmentInformations) {
        QString tmp = doctorIdtoEmployeeId[i["doctorId"].toString()];
        if(!S.contains(tmp)) S.append(tmp);
    }
    ui->appListComboBox->clear();
    ui->appListComboBox->addItems(S);
}

void MainWindow::loadCaseInfo() {
//    caseInformations.clear();
    Response result = requestSender->rpc(Request("case.listByPatient", patientCredential->get(), QJsonObject{}));
    qDebug() << result.data << "\n";
    if(!result.success) {
        QMessageBox::warning(this, "Warning", "服务器繁忙，请刷新界面重试");
        return;
    }
//    while(!caseInformations.empty()) caseInformations.removeAt(0);
    caseInformations = result.data["cases"].toArray();

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
    Response result = requestSender->rpc(Request("chat.listTopicsByUser", patientCredential->get(), QJsonObject{}));
    qDebug() << result.data << "\n";
    if(!result.success) {
        QMessageBox::warning(this, "Warning", "服务器繁忙，请刷新界面重试");
        return;
    }

    topicInformations.clear();
    QJsonArray topicInform = result.data["topics"].toArray();

    for(QJsonValue i : topicInform) topicInformations.append(i.toObject());

    showTopicInfo("");
}

void MainWindow::loadAppointmentInfo() {
//    appointmentInformations.clear();
    Response result = requestSender->rpc(Request("appointment.listByPatient", patientCredential->get(), QJsonObject{}));
    qDebug() << result.data << "\n";
    if(!result.success) {
        QMessageBox::warning(this, "Warning", "服务器繁忙，请刷新界面重试");
        return;
    }

    appointmentInformations = result.data["appointments"].toArray();
//    while(!appointmentInformations.empty()) appointmentInformations.removeAt(0);

    setAppListComboBox();
    showAppointmentInfo("All Doctors", "All times");
}

void MainWindow::loadInformation(){
    patientId = patientCredential->get()->getUserId();
    qDebug() << "patientId: " + patientId + "\n";

    QJsonObject sendRequest = QJsonObject{
        {"patientId", patientId}
    };

    Response result = requestSender->rpc(Request("patient.fetchInfo", patientCredential->get(), sendRequest));
    qDebug() << result.data << "\n";
    if(!result.success) {
        QMessageBox::warning(this, "Warning", "服务器繁忙，请刷新界面重试");
        return;
    }

    QJsonObject registerData = result.data;
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
//    patientId = registerData["patientId"].toString();
}

void MainWindow::showDoctorInfo(QString depart) {
    QWidget *scrollContent = new QWidget(this); // 滚动区域的内容容器
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent); // 容器的布局
    scrollContent->setLayout(scrollLayout);
    doctorIdtoEmployeeId.clear();
    for(QJsonValue i : doctorInformations) {
        doctorIdtoEmployeeId[i["doctorId"].toString()] = i["employeeId"].toString();
        doctorIdtoDoctorName[i["doctorId"].toString()] = i["name"].toString();
        if(i["department"].toString() == depart || depart == "All") {
            DoctorInfoBrief *p = new DoctorInfoBrief(scrollContent, requestSender, patientCredential);
            p->setDoctorBriefInfo(i["employeeId"].toString(), i["name"].toString(), i["department"].toString(), i["doctorId"].toString());
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
    for(QJsonValue i : appointmentInformations) {
        if((doctorIdtoEmployeeId[i["doctorId"].toString()] == doctorId || doctorId == "All Doctors") && (i["date"].toString() == dateTime || dateTime == "All times")) {
            AppointmentData *p = new AppointmentData(scrollContent, requestSender, patientCredential);
            p->setAppointmentData(doctorIdtoDoctorName[i["doctorId"].toString()], doctorIdtoEmployeeId[i["doctorId"].toString()], i["date"].toString(), i["timeSlot"].toString(), i["status"].toString(), i["appointmentId"].toString());
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
    for(QJsonValue i : caseInformations) {
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
            TopicDataBrief *p = new TopicDataBrief(scrollContent, patientId, requestSender, patientCredential);
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
    for(QJsonValue i : doctorInformations) {
        QString tmp = i["department"].toString();
        if(!S.contains(tmp)) S.append(tmp);
    }
//    qDebug << S << "\n";
    ui->docInfoCOffice->clear();
//    qDebug() << "adding Items\n";
    ui->docInfoCOffice->addItems(S);
}

void MainWindow::loadDoctorInfo() {
    Response result = requestSender->rpc(Request("doctor.fetchAllInfo", patientCredential->get(), QJsonObject{}));
    if(!result.success){
        QMessageBox::warning(this, "Warning", "服务器繁忙，请刷新重试");
        return;
    }
//    while(!doctorInformations.empty()) doctorInformations.removeAt(0);
    qDebug() << result.data << "\n";
    doctorInformations = result.data["doctors"].toArray();

    setDoctorInfoComboBox();
    showDoctorInfo("All");
}

QJsonObject MainWindow::queryByDoctorId(QString Id) {
    for(QJsonValue i : doctorInformations) {
        if(i["employeeId"].toString() == Id) return i.toObject();
    }
    exit(-1);
}

QJsonObject MainWindow::queryByCaseId(QString Id) {
    for(QJsonValue i : caseInformations) {
        if(i["caseId"].toString() == Id) return i.toObject();
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

    Response result = requestSender->rpc(Request("patient.updateInfo", patientCredential->get(), registerData));
    qDebug() << result.data << "\n";

    if(result.success) QMessageBox::information(this, "Congratulations!", "个人信息更新成功！");
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

    Response result = requestSender->rpc(Request("patient.updatePassword", patientCredential->get(), changePassData));
    qDebug() << result.data << "\n";

    if(result.success) QMessageBox::information(this, "Congratulations!", "更改密码成功！");
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
