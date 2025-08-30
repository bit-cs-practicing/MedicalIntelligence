#include "triggerclosewindow.h"

TriggerCloseWindow::TriggerCloseWindow(QWidget *parent) : QWidget(parent)
{

}

TriggerCloseWindow::~TriggerCloseWindow() {

}

void TriggerCloseWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "YeahYeahYeah!\n";
    this->deleteLater(); // 延迟销毁对象
    event->accept();     // 接受关闭事件
}
