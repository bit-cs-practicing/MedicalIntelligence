#ifndef USER_H
#define USER_H

#include "name.h"
#include "idcard.h"
#include "password.h"

class User {
public:
    User(Name name, IdCard idCard, Password password);
    virtual ~User() = 0;

    Name getName() const;
    void setName(const Name &value);

    IdCard getIdCard() const;
    void setIdCard(const IdCard &value);

    Password getPassword() const;
    void setPassword(const Password &value);

private:
    Name name;
    IdCard idCard;
    Password password;
};

#endif // USER_H
