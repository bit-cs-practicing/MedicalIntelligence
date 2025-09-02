#include <QStyleFactory>
#include <QFile>
#include <QApplication>

#include "infra/config/clientconfiguration.h"

#include "doctorlogin.h"
#include "doctor.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QFile file(":/style/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qDebug() << styleSheet;
    a.setStyleSheet(styleSheet);

    auto config = ClientConfiguration("setting.ini");
    RpcClient Sender(QHostAddress(config.loadServerIp()), config.loadServerPort());
    CredentialManager doctorCredential;
    DoctorLogin w(nullptr, &Sender, &doctorCredential);
    w.setMinimumSize(800, 600);
    w.show();
    return a.exec();
}
