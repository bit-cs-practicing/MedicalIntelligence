#ifndef TOPICDATADETAILS_H
#define TOPICDATADETAILS_H

#include <QWidget>
#include <QCloseEvent>
namespace Ui {
class TopicDataDetails;
}

class TopicDataDetails : public QWidget
{
    Q_OBJECT

public:
    explicit TopicDataDetails(QWidget *parent = nullptr, QString S = "", QString T = "");
    ~TopicDataDetails();

private:
    Ui::TopicDataDetails *ui;
    QString topicId, patientUserId;
    void loadMessageInfo();
    void showMessage();
    void sendMessage();
    QList<QJsonObject> messageInformations;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // TOPICDATADETAILS_H
