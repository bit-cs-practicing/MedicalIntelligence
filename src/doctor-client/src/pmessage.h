#ifndef PMESSAGE_H
#define PMESSAGE_H

#include <QWidget>
#include "doctortopicdetail.h"

namespace Ui {
class pMessage;
}

class pMessage : public QWidget
{
    Q_OBJECT

public:
    explicit pMessage(QWidget *parent = nullptr);

    ~pMessage();

private:
    Ui::pMessage *ui;
    doctorTopicDetail *fatherWindow;
    void adjustTextBrowserHeight();
};

#endif // PMESSAGE_H
