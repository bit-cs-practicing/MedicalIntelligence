#include <QApplication>

#include "infra/config/clientconfiguration.h"

#include "doctorlogin.h"
#include "doctor.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto config = ClientConfiguration("setting.ini");
    RpcClient Sender(QHostAddress(config.loadServerIp()), config.loadServerPort());
    CredentialManager doctorCredential;
    DoctorLogin w(nullptr, &Sender, &doctorCredential);
    w.show();
    return a.exec();
}
