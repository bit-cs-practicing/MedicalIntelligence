#include "patientlogin.h"
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString srcPath = QApplication::applicationDirPath() + "/setting.ini";
    QSettings settings(srcPath, QSettings::IniFormat);
    settings.beginGroup("patient");
    QString address = settings.value("ip").toString();
    int port = settings.value("port").toInt();
    settings.endGroup();

    RpcClient Sender(QHostAddress(address), port);
    CredentialManager patientCredential;
    PatientLogin w(nullptr, &Sender, &patientCredential);
    w.show();
    return a.exec();
}
