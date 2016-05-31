#include "../litterales/litterales.h"
#include "../manager/manager.h"
#include <iostream>
#include "../GUI/mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <typeinfo>



int main(int argc, char *argv[])
{
    Entier monEntier(4);
    Entier monEntier2(8);



    // Creation du manager de litterales
    FactoryLitterale& myFactory = FactoryLitterale::getInstance();

    // Creation du controleur
    Controleur controler;

    // On ajoute deux litterales à la pile du controleur
    std::string myString = "3";
    Complexe monComplexe3(monEntier,monEntier2);

    controler.empiler(FactoryLitterale::getInstance(),myString);
    controler.empiler(FactoryLitterale::getInstance(),myString);

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
