#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <unistd.h>




int main(int argc, char *argv[])
{

    Reel monReel(2,14);

    Reel monReelpart1(1,24);
    Reel monReelpart2(7,9);

    Reel monReelpart3(1,24);
    Reel monReelpart4(7,9);

    Complexe monComplexe1(monReelpart1,monReelpart2);
    Complexe monComplexe2(monReelpart3,monReelpart4);

    Entier monEntier(2);
    Entier monEntier2(8);

    monReel.setNb(-0.1000);

    monReel.afficher();

    std::cout<<std::endl;

    // Creation du manager de litterales
/*
    FactoryLitterale& myFactory = FactoryLitterale::getInstance();


    //Litterale* myTest = myFactory.addLitterale("3.14");

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
