TEMPLATE = app
QT += widgets
QT += xml
CONFIG += app_bundle
CONFIG += qt
CONFIG += c++11



FORMS += \
    ../GUI/mainwindow.ui \
    ../GUI/param.ui \
    ../GUI/progedit.ui \
    ../GUI/varedit.ui

HEADERS += \
    ../GUI/mainwindow.h \
    ../litterales/litterales.h \
    ../manager/controleur.h \
    ../manager/factory.h \
    ../operateurs/operateurs.h \
    ../GUI/param.h \
    ../XML/xml_dom.h \
    ../GUI/progedit.h \
    ../GUI/varedit.h

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
    ../operateurs/operateursreel.cpp \
    ../GUI/param.cpp \
    ../XML/xml_dom.cpp \
    ../GUI/progedit.cpp \
    ../GUI/varedit.cpp

