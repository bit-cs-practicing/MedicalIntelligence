#include "doctor.h"
#include "ui_doctor.h"
#include "appotuple.h"
#include "casetuple.h"
#include "topicdatabrief.h"
#include <QString>
#include <QRegularExpressionMatch>
#include <QScrollArea>
#include <QMessageBox>
#include <QThread>
#include <QTableView>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QDateTime>
#include <QDebug>
Doctor::Doctor(QWidget *parent, RpcClient *rClient, CredentialManager *cR) :
    QWidget(parent),
    ui(new Ui::Doctor), doctorCredential(cR), requestSender(rClient)
{
//    ui->tabWidget->setCurrentIndex(0);
//    loadDoctorInfo();
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    loadDoctorInfo();
    ui->doctorName->setReadOnly(true);
    ui->employeeId->setReadOnly(true);
    ui->workschedule->setPlaceholderText("格式示例: 09:00-17:00");
    ui->startTime->setPlaceholderText("格式示例: 2025-8-30T09:00:00");
    ui->endTime->setPlaceholderText("格式示例: 2025-8-30T09:00:00");
    leaveHistory["startTime"] = QString("");
    leaveHistory["endTime"] = QString("");
    appointmentList.clear();
    QWidget *targetPage = ui->tabWidget->findChild<QWidget*>("Home");
    if (targetPage) {
        int index = ui->tabWidget->indexOf(targetPage);
        ui->tabWidget->setCurrentIndex(index);
    }
    m_scrollContent = new QWidget;
    QVBoxLayout *scrollLayout = new QVBoxLayout(m_scrollContent);
    scrollLayout->setAlignment(Qt::AlignTop);
    ui->ListScreen->setWidget(m_scrollContent);
    m_appoId = "";
//    m_caseScrollContent = new QWidget;
//    QVBoxLayout *caseScrollLayout = new QVBoxLayout(m_caseScrollContent);
//    caseScrollLayout->setAlignment(Qt::AlignTop);
//    ui->CaseListScreen->setWidget(m_caseScrollContent);
    m_patientId = "";
}

Doctor::~Doctor()
{
    delete ui;
}



bool Doctor::checkId() {
    QString txt = ui->employeeId->text();
    if (txt.length() != 4 || txt[0] != 'D') return false;
    return true;
}

bool Doctor::checkDepartment() {
    return ui->department->text() != "";
}

bool Doctor::checkRegistrationFee() {
    QString num = ui->registrationFee->text();
    for (int i = 0; i < num.length(); i++) {
        if (!num[i].isDigit()) {
            return false;
        }
    }
    return true;
}

bool Doctor::checkWorkschedule() {
    QString schedule = ui->workschedule->text();
    QRegularExpression regExp("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]-([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    QRegularExpressionMatch match = regExp.match(schedule);
    if (match.hasMatch()) return true;
    return false;
}

bool Doctor::checkDailyPatientLimit() {
    QString num = ui->dailyPatientLimit->text();
    for (int i = 0; i < num.length(); i++) {
        if (!num[i].isDigit()) return false;
    }
    return true;
}

void Doctor::on_doneBtn_clicked() {

    if (!checkDepartment()) {
        QMessageBox::warning(this, "提示", "未填写科室。");
        return;
    }

    if (!checkWorkschedule()) {
        QMessageBox::warning(this, "提示", "工作时间表格式错误。");
        return;
    }

    QStringList times = ui->workschedule->text().split('-');
    if (times.size() != 2) {
        QMessageBox::warning(this, "提示", "工作时间表格式错误。");
        return;
    }

    QTime startTime = QTime::fromString(times[0], "hh:mm");
    QTime endTime = QTime::fromString(times[1], "hh:mm");

    if (!startTime.isValid()) {
        QMessageBox::warning(this, "提示", "开始时间无效。");
        return;
    }

    if (!endTime.isValid()) {
        QMessageBox::warning(this, "提示", "结束时间无效。");
    }

    if (startTime >= endTime) {
        QMessageBox::warning(this, "提示", "开始时间必须早于结束时间。");
        return;
    }

    if (!checkRegistrationFee()) {
        QMessageBox::warning(this, "提示", "挂号费必须为实数。");
        return;
    }

    if (!checkDailyPatientLimit()) {
        QMessageBox::warning(this, "提示", "每日预约人数上限必须为非负整数。");
        return;
    }

    doctorInfo["name"] = ui->doctorName->text();
    doctorInfo["employeeId"] = ui->employeeId->text();
    doctorInfo["department"] = ui->department->text();
    doctorInfo["profile"] = ui->profile->text();
    doctorInfo["photo"] = ui->photo->text();
    doctorInfo["workSchedule"] = ui->workschedule->text();
    doctorInfo["registrationFee"] = ui->registrationFee->text().toDouble();
    doctorInfo["dailyPatientLimit"] = ui->dailyPatientLimit->text().toInt();

    Response result = requestSender->rpc(Request("doctor.updateInfo", doctorCredential->get(), doctorInfo));
    qDebug() << result.data;
    if(!result.success) {
        QMessageBox::warning(this, "提示", "服务器繁忙，请刷新界面重试");
        return;
    }

    QMessageBox::information(this, "提示", "更改个人信息成功！");
//    QThread::sleep(5);
}


bool Doctor::checkPassword() {
    QString txt = ui->newPass->text();
    int len = txt.length();
    if(len < 7 || len > 20) return false;
    for(int i = 0; i < len; ++i) {
        if(!txt[i].isDigit() && !txt[i].isLower() && !txt[i].isUpper()) return false;
    }
    return true;
}

bool Doctor::checkNewPassword() {
    if (ui->checkPass->text() != ui->newPass->text()) return false;
    return true;
}

void Doctor::on_doneBtn2_clicked() {

    if (!checkPassword()) {
        QMessageBox::warning(this, "提示", "密码必须为 7 到 20 位的字符，且只能包含大小写字母与数字。");
        return;
    }

    if (!checkNewPassword()) {
        QMessageBox::warning(this, "提示", "请检查你的密码。");
        return;
    }

    QJsonObject newPasswordData;
    newPasswordData["newPassword"] = ui->newPass->text();
    newPasswordData["oldPassword"] = ui->oldPass->text();

    Response result = requestSender->rpc(Request("doctor.updatePassword", doctorCredential->get(), newPasswordData));

    if(!result.success) {
        QMessageBox::warning(this, "提示", "密码错误!");
        return;
    }

    QMessageBox::information(this, "提示", "更新成功，将在 5 秒后返回首页。");
}

void Doctor::on_selectAppoBtn_clicked()
{
    QVBoxLayout *scrollLayout = qobject_cast<QVBoxLayout*>(m_scrollContent->layout());

    QLayoutItem *child;
    while ((child = scrollLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    QString name = ui->selectName->text();
    loadAppoList(name);
}


void Doctor::loadAppoList(QString tname) {
    QVBoxLayout *scrollLayout = qobject_cast<QVBoxLayout*>(m_scrollContent->layout());
    if (!m_scrollContent->layout()) {
            QVBoxLayout *newLayout = new QVBoxLayout(m_scrollContent);
            newLayout->setAlignment(Qt::AlignTop);
        }
    if (scrollLayout) {
        QLayoutItem *child;
        while ((child = scrollLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    }

    for (QJsonObject i : appointmentList) {
        QString appoId = i["appointmentId"].toString();
        QString patientId = i["patientId"].toString();
        QString name = i["patientName"].toString();
        QString patId = i["patientIdCard"].toString();
        QString date = i["date"].toString();
        QString ts = i["timeSlot"].toString();
        QString st = i["status"].toString();

        if(tname != "" && ((tname.length() == 18 && tname != patId) || (tname.length() != 18 && tname != name))) continue;

        appoTuple *item = new appoTuple(patientId, appoId, name, patId, date, ts, st);
//        qDebug() << i;
        item->setAppointmentDetails(i);
        item->setRequestAndCredential(requestSender, doctorCredential);
        scrollLayout->addWidget(item);
    }
}

void Doctor::on_leaveReqBtn_clicked() {
    QString startTime = ui->startTime->text();
    QString endTime = ui->endTime->text();

    QRegularExpression isoRegex("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])T([01]\\d|2[0-3]):[0-5]\\d:[0-5]\\d$");
    QRegularExpressionMatch smatch = isoRegex.match(startTime);
    if (!smatch.hasMatch()) {
        QMessageBox::warning(this, "提示", "开始时间格式错误。");
        return;
    }
    QRegularExpressionMatch ematch = isoRegex.match(endTime);
    if (!ematch.hasMatch()) {
        QMessageBox::warning(this, "提示", "结束时间格式错误。");
        return;
    }

    QDateTime startDt = QDateTime::fromString(startTime, Qt::ISODate);
    QDateTime endDt = QDateTime::fromString(endTime, Qt::ISODate);
    if (startDt >= endDt) {
        QMessageBox::warning(this, "提示", "开始时间必须早于结束时间。");
        return;
    }

    Response result = requestSender->rpc(Request("attendance.leaveRequest", doctorCredential->get(), QJsonObject{{"startTime", startTime}, {"endTime", endTime}}));

    if (!result.success) {
        QMessageBox::warning(this, "提示", "你还有请假未销, 不能请假。 ");
        return;
    }

    leaveHistory["startTime"] = ui->startTime->text();
    leaveHistory["endTime"] = ui->endTime->text();
    leaved = true;
    QMessageBox::information(this, "提示", "请假成功，在销假之前，你不能再次请假。");
    return;
}


void Doctor::on_leaveCancBtn_clicked() {

    Response result = requestSender->rpc(Request("attendance.fetchLastRequest", doctorCredential->get(), QJsonObject{}));
    qDebug() << result.data;
    if(!result.success){
        QMessageBox::warning(this, "提示", "您没有新的请假");
        return;
    }
    QJsonObject tmp = result.data;
    result = requestSender->rpc(Request("attendance.leaveCancel", doctorCredential->get(), tmp));
    qDebug() << result.data;
    if(!result.success) {
        QMessageBox::warning(this, "提示", "服务器繁忙，请刷新界面重试");
        return;
    }
    QMessageBox::information(this, "提示", "销假成功!");
    return;
}




void Doctor::on_fetcLastRequestBtn_clicked() {

    Response result = requestSender->rpc(Request("attendance.checkIn", doctorCredential->get(), QJsonObject{}));
    qDebug() << result.data;
    if(!result.success){
        QMessageBox::warning(this, "提示", result.message);
        return;
    }
    QMessageBox::information(this, "提示", "签到成功，您的签到时间是：" + result.data["time"].toString());
}


void Doctor::loadDoctorInfo() {
//    qDebug() << "trying";
    qDebug() << doctorCredential->get()->getUserId();
    Response result = requestSender->rpc(Request("doctor.fetchInfo", doctorCredential->get(), QJsonObject{{"doctorId", doctorCredential->get()->getUserId()}}));
    qDebug() << result.data;
    if(!result.success) {
        QMessageBox::warning(this, "提示", "服务器繁忙，请刷新界面重试");
        return;
    }
    doctorInfo = result.data;
    ui->doctorName->setText(doctorInfo["name"].toString());
    ui->employeeId->setText(doctorInfo["employeeId"].toString());
    ui->department->setText(doctorInfo["department"].toString());
    ui->profile->setText(doctorInfo["profile"].toString());
    ui->photo->setText(doctorInfo["photo"].toString());
    ui->workschedule->setText(doctorInfo["workSchedule"].toString());
    ui->registrationFee->setText(QString::number(doctorInfo["registrationFee"].toDouble()));
    ui->dailyPatientLimit->setText(QString::number(doctorInfo["dailyPatientLimit"].toInt()));
}

void Doctor::loadAppInfo() {
    Response result = requestSender->rpc(Request("appointment.listByDoctor", doctorCredential->get(), QJsonObject{{}}));
    qDebug() << result.data;
    if(!result.success) {
        QMessageBox::warning(this, "提示", "服务器繁忙，请刷新界面重试");
        return;
    }
    QJsonArray appList = result.data["appointments"].toArray();
    appointmentList.clear();
    for(QJsonValue i : appList){
        QJsonObject tmp = i.toObject();
        Response result = requestSender->rpc(Request("patient.fetchInfo", doctorCredential->get(), QJsonObject{{"patientId", tmp["patientId"]}}));
        int cnt = 5;
        while(!result.success && cnt--) result = requestSender->rpc(Request("patient.fetchInfo", doctorCredential->get(), QJsonObject{{"patientId", tmp["patientId"]}}));
        if(!result.success){
            QMessageBox::warning(this, "提示", "服务器繁忙，请刷新界面重试");
            return;
        }
        qDebug() << result.data;
        tmp["patientIdCard"] = result.data["idCard"];
        tmp["patientName"] = result.data["name"];
        appointmentList.append(tmp);
    }
    loadAppoList("");
}

void Doctor::loadTopicInfo() {
    Response result = requestSender->rpc(Request("chat.listTopicsByUser", doctorCredential->get(), QJsonObject{}));
    qDebug() << result.data << "\n";
    if(!result.success) {
        QMessageBox::warning(this, "提示", "服务器繁忙，请刷新界面重试");
        return;
    }

    topicInformations.clear();
    QJsonArray topicInform = result.data["topics"].toArray();

    for(QJsonValue i : topicInform) topicInformations.append(i.toObject());

    showTopicInfo("");
}

void Doctor::sortTopicById() {
    std::sort(topicInformations.begin(), topicInformations.end(), [](const QJsonObject &A, const QJsonObject &B){
        return A["topicId"].toString() > B["topicId"].toString();
    });
}

void Doctor::sortTopicByTime() {
    std::sort(topicInformations.begin(), topicInformations.end(), [](const QJsonObject &A, const QJsonObject &B){
        return A["lastMessageTime"].toString() > B["lastMessageTime"].toString();
    });
}

void Doctor::showTopicInfo(QString S) {
    if(ui->topicComboBox->currentText() == "按话题Id排序") sortTopicById();
    else sortTopicByTime();
    QWidget *scrollContent = new QWidget(this);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(scrollLayout);
    for(QJsonObject i : topicInformations) {
        if(i["topicId"] == S || S == "") {
            TopicDataBrief *p = new TopicDataBrief(scrollContent, doctorCredential->get()->getUserId(), requestSender, doctorCredential);
            p->setTopicInfo(i["topicId"].toString(), i["lastMessageTime"].toString());
            p->setParent(this);
            scrollLayout->addWidget(p);
//            p->deleteLater();
        }
    }
    ui->topicScreen->setWidget(scrollContent);
    ui->topicScreen->setWidgetResizable(true);
}

void Doctor::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0) loadDoctorInfo();
    else if(index == 2) loadAppInfo();
    else if(index == 4) {
        loadTopicInfo();
    }
}
