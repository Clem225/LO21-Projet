#include "operateurs.h"
#include <sstream>
#include <iostream>


// Liste des opérateurs reconnus

bool estUnOperateurBinaire(const std::string& c)
{
    bool listOperateurBinaire =
            c=="+" ||
            c=="-" ||
            c=="*" ||
            c=="/" ||
            c=="DIV" ||
            c=="MOD";

    if(listOperateurBinaire)
        return true;

    return false;
}
bool estUnOperateurUnaire(const std::string& c)
{
    bool listOperateurUnaire =
            c=="NEG";

    if(listOperateurUnaire)
        return true;

    return false;
}

bool estOperateur(const std::string& str)
{
    bool listOperateur =
            estUnOperateurBinaire(str) ||
            estUnOperateurUnaire(str);


    if(listOperateur)
        return true;

        return false;

}


/*Opérateurs additionnels*/

Entier* DIV(Entier* e1, Entier* e2) {
        return e1->setValue(e1->getNb()/e2->getNb());
}

Entier* MOD(Entier* e1, Entier* e2) {
        return e1->setValue(static_cast<int>(e1->getNb())%(static_cast<int>(e2->getNb())));
}
