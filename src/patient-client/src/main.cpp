#include "patientlogin.h"
#include "infra/rpcclient/rpcclient.h"
#include "infra/security/credentialmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RpcClient Sender(QHostAddress("127.0.0.1"), 8080);
    CredentialManager patientCredential;
    PatientLogin w(nullptr, &Sender, &patientCredential);
    w.show();
    return a.exec();
}
