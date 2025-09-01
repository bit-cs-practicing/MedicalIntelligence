#ifndef CONSULTATIONDEEPSEEKPROVIDER_H
#define CONSULTATIONDEEPSEEKPROVIDER_H

#include "domain/consultation/consultationprovider.h"

#include <QNetworkAccessManager>

class ConsultationDeepSeekProvider : public ConsultationProvider
{
public:
    ConsultationDeepSeekProvider(const QString& appid, const QString& apikey);
    ConsultationAnswer getAnswer(const ConsultationQuestion& question) const override;
private:
    QString appid, apikey;
};

#endif // CONSULTATIONDEEPSEEKPROVIDER_H
