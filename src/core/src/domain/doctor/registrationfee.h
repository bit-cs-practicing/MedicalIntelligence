#ifndef REGISTRATIONFEE_H
#define REGISTRATIONFEE_H

class RegistrationFee {
public:
    explicit RegistrationFee(double fee);

    double getValue() const;

private:
    double fee;
};

#endif // REGISTRATIONFEE_H
