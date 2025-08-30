#include "patientlogin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PatientLogin w;
    w.show();
    return a.exec();
}
