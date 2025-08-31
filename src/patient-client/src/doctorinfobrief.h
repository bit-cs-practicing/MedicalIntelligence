#ifndef DOCTORINFOBRIEF_H
#define DOCTORINFOBRIEF_H

#include <QWidget>
#include <memory>
namespace Ui {
class DoctorInfoBrief;
}

class MainWindow;

class DoctorInfoBrief : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorInfoBrief(QWidget *parent = nullptr);
    ~DoctorInfoBrief();
    void setDoctorBriefInfo(QString, QString, QString);
    void setFatherMainWindow(MainWindow *p) {fatherMainWindow = p;}

private slots:
    void on_details_clicked();

    void on_pushButton_clicked();

private:
    Ui::DoctorInfoBrief *ui;
    MainWindow *fatherMainWindow;
};

#endif // DOCTORINFOBRIEF_H
