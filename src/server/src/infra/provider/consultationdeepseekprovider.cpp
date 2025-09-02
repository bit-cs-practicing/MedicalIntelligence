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

    if (isTimeOut) {
        qDebug() << "reponse timeout";
        reply->abort();
        throw std::runtime_error("reponse timeout");
    }
    if (reply->error() != QNetworkReply::NoError) {
        QString msg = "HTTP ERROR:" + reply->errorString();
        qDebug() << msg;
        throw std::runtime_error(msg.toStdString());
    }

    QByteArray responseData = reply->readAll();
    qDebug() << "request succcess, reponse:" << responseData << '\n';
    QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
    QJsonObject returnObject(responseDoc.object());
    if (!returnObject.contains("output")) {
        throw std::runtime_error("Parsing failed.");
    }
    if (!returnObject.value("output").isObject()) {
        throw std::runtime_error("Parsing failed.");
    }
    QJsonObject outputObject = returnObject.value("output").toObject();
    if (!outputObject.contains("text")) {
        throw std::runtime_error("Parsing failed.");
    }
    return ConsultationAnswer(outputObject.value("text").toString());
}
