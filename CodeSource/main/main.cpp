#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <typeinfo>



int main(int argc, char *argv[])
{



    Entier e1(2);
    Entier e2(5);

    Entier e3(5);
    Entier e4(6);

    Rationnel r1(3,4);
    Rationnel r2(5,2);

    Reel real1(1.25);

    Complexe c1 (&real1,&e4);

    (r1/real1).afficher();
    std::cout<<std::endl;



    // Creation du manager de litterales
    FactoryLitterale& myFactory = FactoryLitterale::getInstance();

    // Creation du controleur
    Controleur controler;

    // On ajoute deux litterales à la pile du controleur
    std::string myString = "3";
    std::string myString2 = "5";

    controler.empiler(FactoryLitterale::getInstance(),myString);
    controler.empiler(FactoryLitterale::getInstance(),myString2);

    // On envoie la commande d'addition
    controler.commande("+");




/*
    QApplication app(argc, argv);

    MainWindow test;
    test.show();

    return app.exec();
    */
    return 0;
}
