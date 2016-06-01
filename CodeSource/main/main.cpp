#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <typeinfo>



int main(int argc, char *argv[])
{








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
