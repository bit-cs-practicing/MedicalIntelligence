#include "consultationdeepseekprovider.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QUrl>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
#include <QEventLoop>
#include <QTimer>

ConsultationDeepSeekProvider::ConsultationDeepSeekProvider(const QString& appid, const QString& apikey):
    appid(appid), apikey(apikey)
{
}

ConsultationAnswer ConsultationDeepSeekProvider::getAnswer(const ConsultationQuestion& question) const {
    QNetworkAccessManager manager;
    QUrl url(QString("https://dashscope.aliyuncs.com/api/v1/apps/%1/completion").arg(appid));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + apikey).toUtf8());

    QJsonObject inputObject, emptyObject;
    inputObject["prompt"] = question.getValue();
    QJsonObject mainObject;
    mainObject["input"] = inputObject;
    mainObject["parameters"] = emptyObject;
    mainObject["debug"] = emptyObject;
    QByteArray postData = QJsonDocument(mainObject).toJson();
    QNetworkReply* reply = manager.post(request, postData);

    QEventLoop eventLoop;
    QTimer timer;
    timer.setSingleShot(true);
    timer.start(30000);
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    reply->deleteLater();

    bool isTimeOut = true;
    if (timer.isActive()) {
        timer.stop();
        isTimeOut = false;
    }
    QObject::disconnect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QObject::disconnect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);

    static QString errorAnswer("服务器繁忙，请稍后再试。");
    if (isTimeOut) {
        qDebug() << "reponse timeout";
        reply->abort();
        return errorAnswer;
    }
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "HTTP ERROR:" << reply->errorString();
        return errorAnswer;
    }
    QByteArray responseData = reply->readAll();
    qDebug() << "request succcess, reponse:" << responseData;
    return QString(responseData);
}
