#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>
#include <QList>
#include <QJsonObject>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"

namespace Ui {
class Doctor;
}

class Doctor : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr, RpcClient *rClient = nullptr, CredentialManager * cR = nullptr);
    void loadAppoList(QString);
    void loadCaseList();
    void loadDoctorInfo();
    void loadAppInfo();
    void loadCaseInfo(QString);
    void loadTopicInfo();
    ~Doctor();

private slots:
    void on_doneBtn_clicked();
    void on_doneBtn2_clicked();
    void handle_Appo_Action(QString, QString, QString);


    void on_leaveReqBtn_clicked();

    void on_leaveCancBtn_clicked();

    void on_fetcLastRequestBtn_clicked();

    void on_OKBtn_clicked();

    void on_selectAppoBtn_clicked();


    void on_selectBtn_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::Doctor *ui;
    bool checkId();
    bool checkDepartment();
    bool checkWorkschedule();
    bool checkRegistrationFee();
    bool checkDailyPatientLimit();
    bool checkPassword();
    bool checkNewPassword();
    void showTopicInfo(QString);
    void openCase(const QString, bool);
    QList<QJsonObject> appointmentList;
    QList<QJsonObject> caseList;
    QList<QJsonObject> topicInformations;
    QJsonObject leaveHistory;
    bool checkedIn = false;
    bool leaved = false;
    QList<QJsonObject> patientInfo;
    QJsonObject doctorInfo;
    QString m_appoId;
    QString m_patientId;
    QWidget *m_scrollContent;
    QWidget *m_caseScrollContent;
    void addAppointmentItem(const QString &patientId);
    void addCaseItem(const QJsonObject&);
    CredentialManager *doctorCredential;
    RpcClient *requestSender;
    void sortTopicById();
    void sortTopicByTime();
};

#endif // DOCTOR_H
