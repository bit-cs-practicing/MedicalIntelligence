#include "credentialmanager.h"

CredentialManager::CredentialManager(): credential(std::nullopt) {}

void CredentialManager::set(Credential newCredential) {
    credential = newCredential;
}

void CredentialManager::clear() {
    credential.reset();
}

const std::optional<Credential>& CredentialManager::get() const {
    return credential;
}

bool CredentialManager::hasCredential() const {
    return credential.has_value();
}
