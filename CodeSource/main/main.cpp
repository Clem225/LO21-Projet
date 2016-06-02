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
    //(c1*c2).afficher();
    std::cout<<std::endl;


    // Creation du controleur
    Controleur controler;

    // On envoie la commande d'addition
    Litterale* res = controler.commande("3 3 +");
    std::cout<<"Resultat : "; res->afficher(); std::cout<<std::endl;


/*
    QApplication app(argc, argv);

    MainWindow test;
    test.show();

    return app.exec();
    */
    return 0;
}
