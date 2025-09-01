#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CustomTextEdit(QWidget *parent = nullptr);

signals:
    void sendMessage();

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Return && event->modifiers() & Qt::ControlModifier) {
            emit sendMessage();
            return;
        }
        QTextEdit::keyPressEvent(event);
    }
};

#endif // CUSTOMTEXTEDIT_H
