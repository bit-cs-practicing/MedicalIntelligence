message("Qt: $$QT_VERSION")
message("Qmake: $$QMAKE_QMAKE")

TEMPLATE = subdirs

SUBDIRS += \
    src/core \
    src/server \
    src/doctor-client \
    src/patient-client

server.depends = core
doctor-client.depends = core
patient-client.depends = core
