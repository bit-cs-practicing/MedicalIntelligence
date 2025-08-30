#ifndef CASEDATABRIEF_H
#define CASEDATABRIEF_H

#include <QWidget>

namespace Ui {
class CaseDataBrief;
}

class MainWindow;

class CaseDataBrief : public QWidget {
    Q_OBJECT

public:
    explicit CaseDataBrief(QWidget *parent = nullptr);
    void setCaseInfo(QString caseId, QString date);
    void setFatherMainWindow(MainWindow *p){fatherMainWindow = p;}
    ~CaseDataBrief();

private slots:
    void on_details_clicked();

private:
    Ui::CaseDataBrief *ui;
    MainWindow *fatherMainWindow;
};

#endif // CASEDATABRIEF_H
