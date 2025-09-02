#include <QApplication>
#include <QSettings>
#include <QStyleFactory>

#include "infra/config/clientconfiguration.h"
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"

#include "patientlogin.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Macintosh"));
    ClientConfiguration config("setting.ini");
    RpcClient Sender(QHostAddress(config.loadServerIp()), config.loadServerPort());
    CredentialManager patientCredential;
    PatientLogin w(nullptr, &Sender, &patientCredential);
    w.show();
    return a.exec();
}
