TEMPLATE = app
QT += widgets
CONFIG += console
CONFIG += app_bundle
CONFIG += qt
CONFIG += c++11



FORMS += \
    ../GUI/mainwindow.ui

HEADERS += \
    ../GUI/mainwindow.h \
    ../litterales/litterales.h \
    ../manager/controleur.h \
    ../manager/factory.h \
    ../operateurs/operateurs.h

SOURCES += \
    ../GUI/mainwindow.cpp \
    ../litterales/litterales.cpp \
    ../main/main.cpp \
    ../manager/controleur.cpp \
    ../manager/factory.cpp \
    ../operateurs/operateurs.cpp \
    ../operateurs/operateursatome.cpp \
    ../operateurs/operateurscomplexes.cpp \
    ../operateurs/operateursentier.cpp \
    ../operateurs/operateursexpression.cpp \
    ../operateurs/operateursprogramme.cpp \
    ../operateurs/operateursrationnel.cpp \
    ../operateurs/operateursreel.cpp

