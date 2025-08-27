!include("../../../common.pri") {
    error("Could not include common.pri!")
}

include("./googletest.pri")

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_init.h

SOURCES += \
        main.cpp
