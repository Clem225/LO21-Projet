#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <iostream>
#include <string>
#include <stack>

#include "factory.h"
#include "../XML/xml_dom.h"



/*!
 * \file controleur.h
 * \brief Controleur avec Memento
 * \author Blanquet - Martinache
 * \version 0.1
 */


/*!
 * \class Memento
 * \brief Design patern MEMENTO
*/
class Memento
{
private :
    std::stack<Operande*> state;
public:
    /*! \brief Constructeur (MEMENTO) -> Sauvegarde la pile */
    Memento(const std::stack<Operande*> obj): state(obj){}
    /*! \brief (MEMENTO) -> Renvoi la pile sauvegardé */
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
    /*! \brief Constructeur par recopie (utilise au MEMENTO) */
    Controleur(const Controleur& m){pile = m.returnPile();}
    /*! \brief Recopie (SINGLETON) */
    Controleur& operator=(const Controleur& m);
    /*! \brief Destructeur (SINGLETON) */
    virtual ~Controleur(){}

    /*! \brief Sauvegarde le dernier opérateur utilisé */
    std::string lastOP="";
    /*! \brief Sauvegarde la derniere litterale utilisée */
    std::string lastArgs="";

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
    /*! \brief Empile une opérande */
    void empiler(Operande* value );
    /*! \brief Empile une valeur donnée gérée par une factory donnéee */
    void empiler(Factory& facto, std::string value);
    /*! \brief Execute le contenu de la pile */
    void executer();
    /*! \brief Renvoie le contenu de la pile dans un string (les size premiers resultats) */
    std::string pileString(int size);
    /*! \brief Permet la gestion d'un string composé de différentes opérandes separées d'un espace */
    void commande(std::string cmd);
    /*! \brief Renvoi la pile */
    std::stack<Operande*> returnPile() const {return pile;}
    // SINGLETON
    /*! \brief (SINGLETON) */
    static Controleur& getInstance();
    /*! \brief (SINGLETON) */
    static void libererInstance();

    // MEMENTO
    /*! \brief MEMENTO -> met la pile à un état donné */
    void setState(std::stack<Operande*> state){this->pile=state;}
    /*! \brief MEMENTO -> renvoi l'état actuel */
    std::stack<Operande*> getState(){return pile;}
    /*! \brief MEMENTO -> sauvegarde dans le memento l'état actuel*/
    Memento saveStateToMemento() const {return Memento(pile);}
    /*! \brief MEMENTO -> recupere un etat depuis le memento */
    void getStateFromMemento(Memento mem) {pile = mem.getState();}

    // Fonction MEMENTO
    /*! \brief Sauvegarde l'état du controleur */
    void save();
    /*! \brief Undo */
    void undo();
    /*! \brief Redo */
    void redo();
};




// Restore les objets du memento
class CareTaker{
  private:
    std::vector<Memento> mementoList;


    /*! \brief Constructeur (SINGLETON) */
    CareTaker(){}
    /*! \brief Constructeur par recopie(SINGLETON) */
    CareTaker(const CareTaker& m);
    /*! \brief Recopie (SINGLETON) */
    CareTaker& operator=(const CareTaker& m);
    /*! \brief Destructeur (SINGLETON) */
    virtual ~CareTaker(){}

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
    /*! \brief Ajoute un etat dans la liste des mementos */
    void add(Memento state){mementoList.push_back(state);}
    /*! \brief Recupere un etat dans la liste des mementos */
    Memento& get(int index){return mementoList[index];}
    /*! \brief Renvoi le nombre de mementos dans la liste */
    int number() const {return mementoList.size();}
    int current=0;


    /*! \brief (SINGLETON) */
    static CareTaker& getInstance();
    /*! \brief (SINGLETON) */
    static void libererInstance();
};

#endif
