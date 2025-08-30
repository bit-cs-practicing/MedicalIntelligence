#ifndef PATIENTREGISTER_H
#define PATIENTREGISTER_H

#include <QWidget>
//#include "patientlogin.h"
namespace Ui {
class PatientRegister;
}
class PatientLogin;
class PatientRegister : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRegister(QWidget *parent = nullptr);
    void setLoginBoard(PatientLogin *tmp) {loginBoard = tmp;}
    ~PatientRegister();

private slots:
    void on_register_2_clicked();

private:
    Ui::PatientRegister *ui;
    bool checkIdCard();
    bool checkPassword();
    bool checkPhone(QString);
    bool checkName();
    bool checkEmail();
    PatientLogin *loginBoard;
};

#endif // PATIENTREGISTER_H
