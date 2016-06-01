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
    ../GUI/mainwindow.cpp \
    ../litterales/operateursentier.cpp \
    ../litterales/operateursrationnel.cpp \
    ../litterales/operateursreel.cpp \
    ../litterales/operateurscomplexes.cpp

HEADERS += \
    ../litterales/litterales.h \
    ../manager/manager.h \
    ../litterales/operateurs.h \
    ../GUI/mainwindow.h

FORMS += \
    ../GUI/mainwindow.ui

