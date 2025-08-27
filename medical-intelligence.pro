message("Qt: $$QT_VERSION")
message("Qmake: $$QMAKE_QMAKE")

TEMPLATE = subdirs

SUBDIRS += \
    src/core \
    src/core/test/core-test.pro \
    src/server \
    src/server/test/server-test.pro \
    src/doctor-client \
    src/doctor-client/test/doctor-client-test.pro \
    src/patient-client \
    src/patient-client/test/patient-client-test.pro

server.depends = core
doctor-client.depends = core
patient-client.depends = core
