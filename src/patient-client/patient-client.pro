QT += core gui

!include("../../common.pri") {
    error("Could not include common.pri!")
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/mainwindow.h

FORMS += \
    src/mainwindow.ui

INCLUDEPATH += $$PWD/../core/src/
DEPENDPATH += $$PWD/../core/src/

win32-g++ {
    exists($$OUT_PWD/../core/libcore.a) {
        PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
        LIBS += -L$$OUT_PWD/../core -lcore
    } else:exists($$OUT_PWD/../core/debug/libcore.a) {
        PRE_TARGETDEPS += $$OUT_PWD/../core/debug/libcore.a
        LIBS += -L$$OUT_PWD/../core/debug -lcore
    } else:exists($$OUT_PWD/../core/release/libcore.a) {
        PRE_TARGETDEPS += $$OUT_PWD/../core/release/libcore.a
        LIBS += -L$$OUT_PWD/../core/release -lcore
    }
} else:win32:!win32-g++ {
    exists($$OUT_PWD/../core/core.lib) {
        PRE_TARGETDEPS += $$OUT_PWD/../core/core.lib
        LIBS += -L$$OUT_PWD/../core -lcore
    } else:exists($$OUT_PWD/../core/debug/core.lib) {
        PRE_TARGETDEPS += $$OUT_PWD/../core/debug/core.lib
        LIBS += -L$$OUT_PWD/../core/debug -lcore
    } else:exists($$OUT_PWD/../core/release/core.lib) {
        PRE_TARGETDEPS += $$OUT_PWD/../core/release/core.lib
        LIBS += -L$$OUT_PWD/../core/release -lcore
    }
} else:unix {
    PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
    LIBS += -L$$OUT_PWD/../core -lcore
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
