#ifndef DOCTORAPPSERVICEIMPL_H
#define DOCTORAPPSERVICEIMPL_H

#include <memory>

#include "../../domain/doctor/doctor.h"
#include "../../domain/doctor/doctorrepository.h"
#include "../../domain/doctor/doctorfactory.h"
#include "../../domain/doctor/doctorservice.h"
#include "../../infra/security/credential.h"
#include "../../infra/security/credentialregistry.h"
#include "doctorappservice.h"

class DoctorAppServiceImpl : public DoctorAppService {
public:
    DoctorAppServiceImpl(
        std::shared_ptr<DoctorRepository> doctorRepository,
        std::shared_ptr<DoctorFactory> doctorFactory,
        std::shared_ptr<DoctorService> doctorService,
        std::shared_ptr<CredentialRegistry> credentialRegistry
    );

    virtual QJsonObject signup(const QJsonObject& data) override;
    virtual QJsonObject login(const QJsonObject& data) override;
    virtual QJsonObject updateInfo(const Credential& credential, const QJsonObject& data) override;
    virtual QJsonObject fetchInfo(const QJsonObject& data) const override;
    virtual QJsonObject fetchAllInfo(const QJsonObject& data) const override;
    virtual QJsonObject updatePassword(const Credential& credential, const QJsonObject& data) override;
private:
    std::shared_ptr<DoctorRepository> doctorRepository;
    std::shared_ptr<DoctorFactory> doctorFactory;
    std::shared_ptr<DoctorService> doctorService;
    std::shared_ptr<CredentialRegistry> credentialRegistry;
};

#endif // DOCTORAPPSERVICEIMPL_H
