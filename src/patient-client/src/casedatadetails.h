#ifndef CASEDATADETAILS_H
#define CASEDATADETAILS_H

#include <QWidget>
#include <QCloseEvent>
#include <QDebug>
namespace Ui {
class CaseDataDetails;
}

class CaseDataDetails : public QWidget
{
    Q_OBJECT

public:
    explicit CaseDataDetails(QWidget *parent = nullptr);
    void setCaseDataDetails(QJsonObject);
    ~CaseDataDetails();

private:
    Ui::CaseDataDetails *ui;

protected:
    void closeEvent(QCloseEvent *event) override {
//        qDebug() << "yesyeah\n";
        this->deleteLater();
        event->accept();
    }
};

#endif // CASEDATADETAILS_H
