#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <unistd.h>




int main(int argc, char *argv[])
{

    Reel monTestt(4,14);
    monTestt.setNb(5.556);
    monTestt.afficher();


    // Creation du manager de litterales
    FactoryLitterale& myFactory = FactoryLitterale::getInstance();


    //Litterale* myTest = myFactory.addLitterale("3.14");
/*
    Reel* monReel = dynamic_cast<Reel*>(myTest);

    monReel->setNb(434.43432000);
*/

/*
    QApplication app(argc, argv);

    MainWindow test;
    test.show();

    return app.exec();
    */
    return 0;
}
