#include "clientconfiguration.h"

ClientConfiguration::ClientConfiguration(const QString& iniFileName)
    : BaseConfiguration(iniFileName)
{
}

auto ClientConfiguration::loadServerIp() const -> QString {
    return getStringValue("server/ip").value_or("0.0.0.0");
}

auto ClientConfiguration::loadServerPort() const -> int {
    return getIntValue("server/port").value_or(8080);
}
