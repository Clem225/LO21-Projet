TEMPLATE = app
QT += widgets
CONFIG += console
CONFIG += app_bundle
CONFIG += qt
CONFIG += c++11

SOURCES += \
    ../main/main.cpp \
    ../litterales/litterales.cpp \
    ../GUI/mainwindow.cpp \
    ../litterales/operateursentier.cpp \
    ../litterales/operateursrationnel.cpp \
    ../litterales/operateursreel.cpp \
    ../litterales/operateurscomplexes.cpp \
    ../litterales/operateursprogramme.cpp \
    ../litterales/operateursexpression.cpp \
    ../litterales/operateursatome.cpp \
    ../operateurs/operateurs.cpp \
    ../manager/factory.cpp \
    ../manager/controleur.cpp

HEADERS += \
    ../litterales/litterales.h \
    ../litterales/operateurs.h \
    ../GUI/mainwindow.h \
    ../manager/factory.h \
    ../manager/controleur.h

FORMS += \
    ../GUI/mainwindow.ui

