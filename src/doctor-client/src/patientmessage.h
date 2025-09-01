#ifndef PATIENTMESSAGE_H
#define PATIENTMESSAGE_H

#include <QWidget>

namespace Ui {
class PatientMessage;
}

class TopicDataDetails;

class PatientMessage : public QWidget
{
    Q_OBJECT

public:
    explicit PatientMessage(QWidget *parent = nullptr, TopicDataDetails *father = nullptr);
    void setPatientMessage(QString, QString);
    void setTextEnabled(bool);
    ~PatientMessage();

private:
    Ui::PatientMessage *ui;
    TopicDataDetails *fatherWindow;
    void adjustTextBrowserHeight();
};

#endif // PATIENTMESSAGE_H
