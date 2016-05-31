#ifndef MANAGER_H
#define MANAGER_H
#include <stack>
#include <iostream>
#include <string>

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
 * \class FactoryLitterale
 * \brief Création de litterale (Design Patern Factory Method)
*/

class Litterale;

class FactoryLitterale
{

// SINGLETON
    private :
        FactoryLitterale(){}
        FactoryLitterale(const FactoryLitterale& m){}
        FactoryLitterale& operator=(const FactoryLitterale& m){}
        ~FactoryLitterale(){}


        // On utilise une structure, les attributs sont publiques donc pas besoin d'amitie
        struct Handler {
        FactoryLitterale* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
        };

        static Handler handler;

    public:
        static FactoryLitterale& getInstance();
        static void libererInstance();
        // On donne un string en entrée à addLitterale qui renvera une reference vers un objet correspondant
        Litterale* addLitterale(std::string litterale);


};

class Controleur {
private :
    std::stack<Litterale*> pile;
public :
    void empiler(FactoryLitterale& facto, std::string value){pile.push(facto.addLitterale(value));}
    void commande(const std::string& c);
};


#endif
