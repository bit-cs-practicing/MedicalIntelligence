#include "credentialregistry.h"

CredentialRegistry::CredentialRegistry() {

}

void CredentialRegistry::add(Credential credential) {
    std::lock_guard<std::mutex> lock(mutex);
    reg.insert(credential.getUserId(), credential);
}

void CredentialRegistry::revoke(const Credential& credential) {
    std::lock_guard<std::mutex> lock(mutex);
    reg.remove(credential.getUserId());
}

bool CredentialRegistry::contains(const Credential& credential) const {
    std::lock_guard<std::mutex> lock(mutex);
    auto iter = reg.find(credential.getUserId());
    return iter != reg.end() && iter->toString() == credential.toString();
}

void CredentialRegistry::check(const Credential &credential) const {
    if (!contains(credential)) {
        throw std::logic_error("无效凭证");
    }
}
