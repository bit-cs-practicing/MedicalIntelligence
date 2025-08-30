#ifndef TOPICDATABRIEF_H
#define TOPICDATABRIEF_H

#include <QWidget>

namespace Ui {
class TopicDataBrief;
}

class TopicDataDetails;

class TopicDataBrief : public QWidget
{
    Q_OBJECT

public:
    explicit TopicDataBrief(QWidget *parent = nullptr, QString patientUserId = "");
    void setTopicInfo(QString S1, QString S2);
    ~TopicDataBrief();

private slots:
    void on_details_clicked();

private:
    Ui::TopicDataBrief *ui;
    QString patientUserId;
//    TopicDataDetails *detailWindow;
};

#endif // TOPICDATABRIEF_H
