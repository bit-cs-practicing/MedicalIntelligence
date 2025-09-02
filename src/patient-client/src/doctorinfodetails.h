#ifndef DOCTORINFODETAILS_H
#define DOCTORINFODETAILS_H

#include <QWidget>
#include <QCloseEvent>
#include <QDebug>
#include "imagedownloader.h"
namespace Ui {
class DoctorInfoDetails;
}

class DoctorInfoDetails : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorInfoDetails(QWidget *parent = nullptr);
    void setInformations(QJsonObject info);
    ~DoctorInfoDetails();

private:
    Ui::DoctorInfoDetails *ui;
    ImageDownloader *downloader;

private slots:
    void onImageDownloaded(const QPixmap &pixmap);


protected:
    void closeEvent(QCloseEvent *event) override {
//        qDebug() << "yesyeah\n";
        this->deleteLater();
        event->accept();
    }
};

#endif // DOCTORINFODETAILS_H
