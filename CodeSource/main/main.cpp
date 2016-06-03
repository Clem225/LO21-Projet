#include "../litterales/litterales.h"
#include "../manager/controleur.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <typeinfo>



int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    MainWindow principale;
    principale.show();

    return app.exec();
}
