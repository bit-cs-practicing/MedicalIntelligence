#include "serverconfiguration.h"

ServerConfiguration::ServerConfiguration(const QString& iniFileName)
    : BaseConfiguration(iniFileName)
{
}

auto ServerConfiguration::loadDatabaseName() const -> QString {
    return getStringValue("database/path").value_or("main.db");
}

auto ServerConfiguration::loadServerIp() const -> QString {
    return getStringValue("server/ip").value_or("0.0.0.0");
}

auto ServerConfiguration::loadServerPort() const -> int {
    return getIntValue("server/port").value_or(8080);
}

auto ServerConfiguration::loadAgentApiKey() const -> QString {
    if (auto res = getStringValue("agent/api-key")) {
        return res.value();
    } else {
        throw std::runtime_error("agent/api-key 未配置");
    }
}

auto ServerConfiguration::loadAgentDoctorAssistantAppKey() const -> QString {
    if (auto res = getStringValue("agent/doctor-assistant-app-key")) {
        return res.value();
    } else {
        throw std::runtime_error("agent/doctor-assistant-app-key 未配置");
    }
}

auto ServerConfiguration::loadAgentPatientAssistantAppKey() const -> QString {
    if (auto res = getStringValue("agent/patient-assistant-app-key")) {
        return res.value();
    } else {
        throw std::runtime_error("agent/patient-assistant-app-key 未配置");
    }
}
