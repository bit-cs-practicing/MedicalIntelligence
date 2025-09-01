#ifndef SERVERCONFIGURATION_H
#define SERVERCONFIGURATION_H

#include "baseconfiguration.h"

class ServerConfiguration : public BaseConfiguration {
public:
    ServerConfiguration(const QString& iniFileName);

    auto loadDatabaseName() const -> QString;
    auto loadServerIp() const -> QString;
    auto loadServerPort() const -> int;
    auto loadAgentApiKey() const -> QString;
    auto loadAgentDoctorAssistantAppKey() const -> QString;
    auto loadAgentPatientAssistantAppKey() const -> QString;
};

#endif // SERVERCONFIGURATION_H
