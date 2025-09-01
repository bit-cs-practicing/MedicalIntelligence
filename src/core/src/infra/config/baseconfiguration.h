#ifndef BASECONFIGURATION_H
#define BASECONFIGURATION_H

#include <optional>

#include <QSettings>
#include <QString>

class BaseConfiguration {
public:
    BaseConfiguration(QString fileName);
protected:
    std::optional<QString> getStringValue(const QString& key) const;
    std::optional<int> getIntValue(const QString& key) const;
    std::optional<bool> getBoolValue(const QString& key) const;
private:
    QSettings config;
};

#endif // BASECONFIGURATION_H
