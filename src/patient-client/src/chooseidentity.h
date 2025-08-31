#ifndef CHOOSEIDENTITY_H
#define CHOOSEIDENTITY_H
#include <memory>
#include <QMainWindow>
#include "patientlogin.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ChooseIdentity; }
QT_END_NAMESPACE

class ChooseIdentity : public QMainWindow
{
    Q_OBJECT

public:
    ChooseIdentity(QWidget *parent = nullptr);
    ~ChooseIdentity();

private slots:
    void on_Patient_clicked();

private:
    Ui::ChooseIdentity *ui;
    std::unique_ptr<PatientLogin> loginBoard;
//    PatientLogin *loginBoard;
};
#endif // CHOOSEIDENTITY_H
