#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <typeinfo>



int main(int argc, char *argv[])
{



    Entier e1(2);
    Entier e2(5);

    Entier e3(7);
    Entier e4(6);

    Rationnel r1(3,4);
    Rationnel r2(5,2);

    Reel real1(1.25);
    Reel real2 (2.25);
    Reel real3 (5.12);

    Complexe c1 (&e3,&r1);
    Complexe c2 (&real1,&real2);

    (c1-c2).afficher();
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
