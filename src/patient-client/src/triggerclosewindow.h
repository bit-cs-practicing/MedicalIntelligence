#ifndef TRIGGERCLOSEWINDOW_H
#define TRIGGERCLOSEWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>
class TriggerCloseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TriggerCloseWindow(QWidget *parent = nullptr);
    ~TriggerCloseWindow();
signals:

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // TRIGGERCLOSEWINDOW_H
