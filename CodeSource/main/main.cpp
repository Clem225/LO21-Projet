#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <unistd.h>




int main(int argc, char *argv[])
{

    Reel monReel(2);

    Reel monReelpart1(2);
    Reel monReelpart2(4);

    Reel monReelpart3(1.24);
    Reel monReelpart4(7.9);

    Complexe monComplexe1(monReelpart1,monReelpart2);
    Complexe monComplexe2(monReelpart3,monReelpart4);

    Entier monEntier(4);
    Entier monEntier2(8);

    Rationnel monRat(3,4);

    (monEntier/monRat).afficher();

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
