#ifndef DOCTORTOPICDETAIL_H
#define DOCTORTOPICDETAIL_H

#include <QWidget>

namespace Ui {
class doctorTopicDetail;
}

class doctorTopicDetail : public QWidget
{
    Q_OBJECT

public:
    explicit doctorTopicDetail(QWidget *parent = nullptr);
    ~doctorTopicDetail();

private:
    Ui::doctorTopicDetail *ui;
};

#endif // DOCTORTOPICDETAIL_H
