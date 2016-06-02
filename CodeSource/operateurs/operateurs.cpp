#include <iostream>

// Liste des opérateurs reconnus

bool estUnOperateurBinaire(const std::string& c)
{
    bool listOperateurBinaire =
            c=="+" ||
            c=="-" ||
            c=="*" ||
            c=="/";

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

bool estOperateur(std::string& str)
{
    bool listOperateur =
            estUnOperateurBinaire(str) ||
            estUnOperateurUnaire(str);


    if(listOperateur)
        return true;

        return false;

}
