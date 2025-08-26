CONFIG += c++17
CONFIG += warn_on

CONFIG(release, debug|release) {
    CONFIG += optimize_full
}

UI_DIR = ui
MOC_DIR = moc
RCC_DIR = rcc
OBJECTS_DIR = obj

INCLUDEPATH += .
