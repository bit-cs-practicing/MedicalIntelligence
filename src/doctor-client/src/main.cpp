#include "doctorlogin.h"
#include "doctor.h"

#include <QApplication>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString srcPath = QApplication::applicationDirPath() + "/setting.ini";
    QSettings settings(srcPath, QSettings::IniFormat);
    settings.beginGroup("doctor");
    if (!settings.contains("ip")) {
        settings.setValue("ip", "127.0.0.1");
    }
    if (!settings.contains("port")) {
        settings.setValue("port", 8080);
    }
    QString address = settings.value("ip").toString();
    int port = settings.value("port").toInt();
    settings.endGroup();

    RpcClient Sender(QHostAddress(address), port);
    CredentialManager doctorCredential;
    DoctorLogin w(nullptr, &Sender, &doctorCredential);
    // QObject::connect(&w, &DoctorLogin::loginSucceed, &d, &Doctor::onLoginSuccess);
    w.show();
    return a.exec();
}
