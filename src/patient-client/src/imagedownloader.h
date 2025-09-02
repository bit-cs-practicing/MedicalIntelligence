#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ImageDownloader : public QObject
{
    Q_OBJECT
public:
    explicit ImageDownloader(QObject *parent = nullptr);
    void downloadImage(const QUrl &url);
signals:
    void imageDownloaded(const QPixmap &pixmap);
private slots:
    void onDownloadFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager *manager;
};

#endif // IMAGEDOWNLOADER_H
