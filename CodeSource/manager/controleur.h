#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <iostream>
#include <string>
#include <stack>

#include "factory.h"
#include "../XML/xml_dom.h"



/*!
 * \file manager.h
 * \brief Creation des Factory et du Controleur
 * \author Blanquet - Martinache
 * \version 0.1
 */

// MEMENTO class : COntient l'objet sauvegardé.
class Memento
{
private :
    std::stack<Operande*> state;
public:
    Memento(const std::stack<Operande*> obj): state(obj){}
    std::stack<Operande*> getState() const {return state;}

};

/*!
 * \class Controleur
 * \brief Permet l'empilement et l'execution dans une pile
*/
class Controleur {
    friend class Memento;

private :
    std::stack<Operande*> pile;

    /*! \brief Constructeur (SINGLETON) */
    Controleur(){}
    /*! \brief Constructeur (SINGLETON) */
    // DOIT FONCTIONNER POUR MEMENTO
    Controleur(const Controleur& m){pile = m.returnPile();}
    /*! \brief Recopie (SINGLETON) */
    Controleur& operator=(const Controleur& m){}
    /*! \brief Destructeur (SINGLETON) */
    ~Controleur(){}


    Operande* lastOP=nullptr;
    Operande* lastArgs=nullptr;

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
    void empiler(Operande* value );
    void empiler(Factory& facto, std::string value);
    /*! \brief Execute le contenu de la pile */
    void executer();
    /*! \brief Renvoie le contenu de la pile dans un string */
    std::string pileString(int size);
    /*! \brief Permet la gestion d'un string composé de différentes opérandes separées d'un espace*/
    void commande(std::string cmd);
    std::stack<Operande*> returnPile() const {return pile;}
// SINGLETON
    /*! \brief (SINGLETON) */
    static Controleur& getInstance();
    /*! \brief (SINGLETON) */
    static void libererInstance();

    // MEMENTO

    void setState(std::stack<Operande*> state){this->pile=state;}
    std::stack<Operande*> getState(){return pile;}
    Memento saveStateToMemento() const {return Memento(pile);}
    void getStateFromMemento(Memento mem) {pile = mem.getState();}

    // Fonction MEMENTO
    void save();
    void undo();
    void redo();




};







// Restore les objets du memento
class CareTaker{
  private:
    std::vector<Memento> mementoList;


    // SINGLETON
    /*! \brief Constructeur (SINGLETON) */
    CareTaker(){}
    /*! \brief Constructeur (SINGLETON) */
    // DOIT FONCTIONNER POUR MEMENTO
    CareTaker(const CareTaker& m){}
    /*! \brief Recopie (SINGLETON) */
    CareTaker& operator=(const CareTaker& m){}
    /*! \brief Destructeur (SINGLETON) */
    ~CareTaker(){}


    /*!
     * \class Handler
     * \brief Gestion du singleton (attribut publique, évite l'amitié)
    */
    struct Handler {
    CareTaker* instance;
    Handler():instance(nullptr){}
    ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
    };



    static Handler handler;

public :
    void add(Memento state){mementoList.push_back(state);}
    Memento& get(int index){return mementoList[index];}
    int number() const {return mementoList.size();}
    int current=6;

    // SINGLETON
        /*! \brief (SINGLETON) */
        static CareTaker& getInstance();
        /*! \brief (SINGLETON) */
        static void libererInstance();
};


#endif
