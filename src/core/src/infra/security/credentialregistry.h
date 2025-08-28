#ifndef CREDENTIALREGISTRY_H
#define CREDENTIALREGISTRY_H

#include <mutex>
#include <QMap>

#include "credential.h"

class CredentialRegistry {
public:
    CredentialRegistry();

    void add(Credential credential);
    void revoke(const Credential& credential);
    bool contains(const Credential& crendential) const;
private:
    QMap<QString, Credential> reg;
    mutable std::mutex mutex;
};

#endif // CREDENTIALREGISTRY_H
