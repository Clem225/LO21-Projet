#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Creation du manager de litterales
    FactoryLitterale& myFactory = FactoryLitterale::getInstance();

    Litterale* myTest = myFactory.addLitterale("3.14");

    QApplication app(argc, argv);

    Dialog test;
    test.show();

    return app.exec();
}
