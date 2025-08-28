#ifndef CREDENTIALMANAGER_H
#define CREDENTIALMANAGER_H

#include <optional>

#include "credential.h"

class CredentialManager {
public:
    CredentialManager();

    void set(Credential credential);
    void clear();
    const std::optional<Credential>& get() const;
    bool hasCredential() const;
private:
    std::optional<Credential> credential;
};

#endif // CREDENTIALMANAGER_H
