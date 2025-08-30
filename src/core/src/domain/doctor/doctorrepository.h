#ifndef DOCTORREPOSITORY_H
#define DOCTORREPOSITORY_H

#include "doctor.h"
#include <optional>
#include <QList>

class DoctorRepository {
public:
    virtual ~DoctorRepository() = default;

    virtual void save(const Doctor& doctor) = 0;
    virtual std::optional<Doctor> getById(const Id& id) const = 0;
    virtual std::optional<Doctor> getByIdCard(const IdCard& idCard) const = 0;
    virtual QList<Doctor> getAll() const = 0;
};

#endif // DOCTORREPOSITORY_H
