#ifndef CLIENTCONFIGURATION_H
#define CLIENTCONFIGURATION_H

#include "baseconfiguration.h"

class ClientConfiguration : public BaseConfiguration {
public:
    ClientConfiguration(const QString& iniFileName);

    auto loadServerIp() const -> QString;
    auto loadServerPort() const -> int;
};

#endif // CLIENTCONFIGURATION_H
