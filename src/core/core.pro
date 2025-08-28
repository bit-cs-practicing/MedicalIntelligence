QT -= gui

TEMPLATE = lib
CONFIG += staticlib

!include("../../common.pri") {
    error("Could not include common.pri!")
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core.cpp \
    src/domain/appointment/appointment.cpp \
    src/domain/appointment/appointmentstatus.cpp \
    src/domain/appointment/appointmenttimeslot.cpp \
    src/domain/attendance/attendance.cpp \
    src/domain/case/case.cpp \
    src/domain/case/caseadvice.cpp \
    src/domain/case/casediagnosis.cpp \
    src/domain/case/caseprescription.cpp \
    src/domain/doctor/dailypatientlimit.cpp \
    src/domain/doctor/department.cpp \
    src/domain/doctor/doctor.cpp \
    src/domain/doctor/employeeid.cpp \
    src/domain/doctor/profile.cpp \
    src/domain/doctor/registrationfee.cpp \
    src/domain/doctor/workschedule.cpp \
    src/domain/id.cpp \
    src/domain/leave/leaveperiod.cpp \
    src/domain/leave/leaverecord.cpp \
    src/domain/leave/leavestatus.cpp \
    src/domain/message/message.cpp \
    src/domain/message/messagecontent.cpp \
    src/domain/patient/birthday.cpp \
    src/domain/patient/email.cpp \
    src/domain/patient/gender.cpp \
    src/domain/patient/patient.cpp \
    src/domain/topic/topic.cpp \
    src/domain/user/idcard.cpp \
    src/domain/user/name.cpp \
    src/domain/user/password.cpp \
    src/domain/patient/phone.cpp \
    src/domain/user/user.cpp \
    src/infra/security/credential.cpp \
    src/infra/security/credentialmanager.cpp \
    src/infra/security/credentialregistry.cpp

HEADERS += \
    src/core.h \
    src/domain/appointment/appointment.h \
    src/domain/appointment/appointmentstatus.h \
    src/domain/appointment/appointmenttimeslot.h \
    src/domain/attendance/attendance.h \
    src/domain/case/case.h \
    src/domain/case/caseadvice.h \
    src/domain/case/casediagnosis.h \
    src/domain/case/caseprescription.h \
    src/domain/doctor/dailypatientlimit.h \
    src/domain/doctor/department.h \
    src/domain/doctor/doctor.h \
    src/domain/doctor/employeeid.h \
    src/domain/doctor/profile.h \
    src/domain/doctor/registrationfee.h \
    src/domain/doctor/workschedule.h \
    src/domain/id.h \
    src/domain/leave/leaveperiod.h \
    src/domain/leave/leaverecord.h \
    src/domain/leave/leavestatus.h \
    src/domain/message/message.h \
    src/domain/message/messagecontent.h \
    src/domain/patient/birthday.h \
    src/domain/patient/email.h \
    src/domain/patient/gender.h \
    src/domain/patient/patient.h \
    src/domain/topic/topic.h \
    src/domain/user/idcard.h \
    src/domain/user/name.h \
    src/domain/user/password.h \
    src/domain/patient/phone.h \
    src/domain/user/user.h \
    src/infra/security/credential.h \
    src/infra/security/credentialmanager.h \
    src/infra/security/credentialregistry.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
