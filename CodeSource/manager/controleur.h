#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include <stack>
#include <iostream>
#include <string>

#include "../litterales/litterales.h"

/*!
 * \file manager.h
 * \brief Creation des Factory et du Controleur
 * \author Blanquet - Martinache
 * \version 0.1
 */

/*!
 * \class LitteraleException
 * \brief Gestion des erreurs due à des littterales
*/
class LitteraleException {
    std::string info;
public:
    LitteraleException(const std::string& str):info(str){}
    std::string getInfo() const { return info; }
};

/*!
 * \class Factory
 * \brief Création de operateurs ou de litterale (pere des deux factorys)
*/

class Factory
{
public :
        virtual Operande* create(std::string value) = 0;
};


/*!
 * \class Controleur
 * \brief Permet l'empilement et l'execution dans une pile
*/

class Controleur {
private :
    std::stack<Operande*> pile;

    // SINGLETON
    Controleur(){}
    Controleur(const Controleur& m){}
    Controleur& operator=(const Controleur& m){}
    ~Controleur(){}

    // On utilise une structure, les attributs sont publiques donc pas besoin d'amitie
    struct Handler {
    Controleur* instance;
    Handler():instance(nullptr){}
    ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
    };

    static Handler handler;

public :
    void empiler(Factory& facto, std::string value){pile.push(facto.create(value));}
    void executer();
    std::string pileString();
    void commande(std::string cmd);

// SINGLETON
    static Controleur& getInstance();
    static void libererInstance();
    Operande* create(std::string value);
};


#endif
