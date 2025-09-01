#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QJsonArray>
#include <map>
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, RpcClient *rSender = nullptr, CredentialManager *pC = nullptr);
    ~MainWindow();
    void loadInformation();
    void loadDoctorInfo();
    void loadCaseInfo();
    void loadAppointmentInfo();
    void loadTopicInfo();
    void setDoctorInfoComboBox();
    void setAppListComboBox();
    void showDoctorInfo(QString);
    void showAppointmentInfo(QString, QString);
    void showCaseInfo(QString);
    void showTopicInfo(QString);
    void sortTopicById();
    void sortTopicByTime();
    void setPatientId(QString S){patientId = S;}
    QJsonObject queryByDoctorId(QString Id);
    QJsonObject queryByCaseId(QString Id);

private slots:
    void on_Tabs_tabBarClicked(int index);

    void on_changeinfoBtn_clicked();

    void on_updPassBtn_clicked();

    void on_docInfoCheck_clicked();


    void on_appListCheck_clicked();

    void on_caseCheckBtn_clicked();

    void on_topicCheckBtn_clicked();

private:
    Ui::MainWindow *ui;
    bool checkPhone(QString);
    bool checkEmail();
    bool checkPassword(QString);
    QString patientId;
    QJsonArray doctorInformations;
    QJsonArray appointmentInformations;
    QJsonArray caseInformations;
    QList<QJsonObject> topicInformations;
    CredentialManager *patientCredential;
    RpcClient *requestSender;
    std::map<QString, QString> doctorIdtoEmployeeId;
    std::map<QString, QString> doctorIdtoDoctorName;
};

#endif // MAINWINDOW_H
