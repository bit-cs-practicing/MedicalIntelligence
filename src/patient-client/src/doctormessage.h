#ifndef DOCTORMESSAGE_H
#define DOCTORMESSAGE_H

#include <QWidget>

namespace Ui {
class DoctorMessage;
}

class TopicDataDetails;

class DoctorMessage : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorMessage(QWidget *parent = nullptr, TopicDataDetails *father = nullptr);
    void setDoctorMessage(QString name, QString content);
//    void setFatherWindow(TopicDataDetails *p){fatherWindow = p;}
    ~DoctorMessage();

private:
    Ui::DoctorMessage *ui;
    void adjustTextBrowserHeight();
    TopicDataDetails *fatherWindow;
};

#endif // DOCTORMESSAGE_H
