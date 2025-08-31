#ifndef USER_H
#define USER_H

#include "domain/id.h"

#include "idcard.h"
#include "name.h"
#include "password.h"

class User {
public:
    static const QString ROLE_DOCTOR;
    static const QString ROLE_PATIENT;

    User(Name name, IdCard idCard, Password password);
    virtual ~User() = default;

    Name getName() const;
    void setName(const Name &value);

    IdCard getIdCard() const;
    void setIdCard(const IdCard &value);

    Password getPassword() const;
    void setPassword(const Password &value);

    Id getId() const;
    virtual QString getRole() const = 0;
private:
    Name name;
    IdCard idCard;
    Password password;
};

#endif // USER_H
