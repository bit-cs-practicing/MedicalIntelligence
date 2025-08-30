#ifndef PATIENTLOGIN_H
#define PATIENTLOGIN_H
#include <memory>
#include <QWidget>
#include "patientregister.h"
#include "mainwindow.h"
namespace Ui {
class PatientLogin;
}

class PatientLogin : public QWidget
{
    Q_OBJECT

public:
    explicit PatientLogin(QWidget *parent = nullptr);
    ~PatientLogin();

private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::PatientLogin *ui;
    bool checkUsername();
    bool checkPassword();
    std::unique_ptr<PatientRegister> registerBoard;
    std::unique_ptr<MainWindow> patientWindow;
//    PatientRegister *registerBoard;
};

#endif // PATIENTLOGIN_H
