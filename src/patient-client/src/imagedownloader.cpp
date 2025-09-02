#include "imagedownloader.h"

ImageDownloader::ImageDownloader(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &ImageDownloader::onDownloadFinished);
}

void ImageDownloader::downloadImage(const QUrl &url) {
    QNetworkRequest request(url);
    manager->get(request);
}

void ImageDownloader::onDownloadFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Download error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray imageData = reply->readAll();
    reply->deleteLater();

    QPixmap pixmap;
    if (pixmap.loadFromData(imageData)) {
        emit imageDownloaded(pixmap);
    } else {
        qDebug() << "Failed to load image from data";
    }
}
