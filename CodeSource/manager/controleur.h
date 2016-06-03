#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <iostream>
#include <string>
#include <stack>

#include "factory.h"


/*!
 * \file manager.h
 * \brief Creation des Factory et du Controleur
 * \author Blanquet - Martinache
 * \version 0.1
 */


/*!
 * \class Controleur
 * \brief Permet l'empilement et l'execution dans une pile
*/
class Controleur {
private :
    std::stack<Operande*> pile;

    /*! \brief Constructeur (SINGLETON) */
    Controleur(){}
    /*! \brief Constructeur (SINGLETON) */
    Controleur(const Controleur& m){}
    /*! \brief Recopie (SINGLETON) */
    Controleur& operator=(const Controleur& m){}
    /*! \brief Destructeur (SINGLETON) */
    ~Controleur(){}


    /*!
     * \class Handler
     * \brief Gestion du singleton (attribut publique, évite l'amitié)
    */
    struct Handler {
    Controleur* instance;
    Handler():instance(nullptr){}
    ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
    };

    static Handler handler;

public :
    /*! \brief Empile une valeur donnée gérée par une factory donnéee */
    void empiler(Factory& facto, std::string value){pile.push(facto.create(value));}
    /*! \brief Execute le contenu de la pile */
    void executer();
    /*! \brief Renvoie le contenu de la pile dans un string */
    std::string pileString();
    /*! \brief Permet la gestion d'un string composé de différentes opérandes separées d'un espace*/
    void commande(std::string cmd);

// SINGLETON
    /*! \brief (SINGLETON) */
    static Controleur& getInstance();
    /*! \brief (SINGLETON) */
    static void libererInstance();




};


#endif
