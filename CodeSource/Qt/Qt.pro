TEMPLATE = app
QT += widgets
CONFIG += console
CONFIG += app_bundle
CONFIG += qt
CONFIG += c++11

SOURCES += \
    ../main/main.cpp \
    ../litterales/litterales.cpp \
    ../manager/manager.cpp \
    ../litterales/operateurs.cpp \
    ../GUI/mainwindow.cpp

HEADERS += \
    ../litterales/litterales.h \
    ../manager/manager.h \
    ../litterales/operateurs.h \
    ../GUI/mainwindow.h

FORMS += \
    ../GUI/mainwindow.ui

