#include "baseconfiguration.h"

#include <QCoreApplication>

BaseConfiguration::BaseConfiguration(QString iniFileName)
    : config(QCoreApplication::applicationDirPath() + "/" + iniFileName, QSettings::IniFormat)
{
}

std::optional<QString> BaseConfiguration::getStringValue(const QString &key) const {
    return (config.contains(key) ? std::make_optional(config.value(key).toString()) : std::nullopt);
}

std::optional<int> BaseConfiguration::getIntValue(const QString &key) const {
    return (config.contains(key) ? std::make_optional(config.value(key).toInt()) : std::nullopt);

}

std::optional<bool> BaseConfiguration::getBoolValue(const QString &key) const {
    return (config.contains(key) ? std::make_optional(config.value(key).toBool()) : std::nullopt);
}
