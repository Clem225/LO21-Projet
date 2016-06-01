#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <typeinfo>



int main(int argc, char *argv[])
{

    Entier e1(1);
    Entier e2(2);
    Entier e3(3);
    Entier e4(4);

    Rationnel r1(3,4);

    Reel real1(3.14);
    Reel real2(5.12);

    Complexe c1(&real1,&e4);
    Complexe c2(&real2,&e3);
    (c1*c2).afficher();
    std::cout<<std::endl;






    // Creation du manager de litterales
    FactoryLitterale& myFactory = FactoryLitterale::getInstance();




    // Creation du manager de operateurs
    FactoryOperateur& myFactory2 = FactoryOperateur::getInstance();


    // Creation du controleur
    Controleur controler;

    // On ajoute deux litterales à la pile du controleur
    std::string myString = "3";
    std::string myString2 = "5";
    std::string myString3 = "+";

    controler.empiler(FactoryLitterale::getInstance(),myString);
    controler.empiler(FactoryLitterale::getInstance(),myString2);
    controler.empiler(FactoryOperateur::getInstance(),myString3);

    // On envoie la commande d'addition
    controler.executer();




/*
    QApplication app(argc, argv);

    MainWindow test;
    test.show();

    return app.exec();
    */
    return 0;
}
