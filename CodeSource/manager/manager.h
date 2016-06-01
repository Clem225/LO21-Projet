#ifndef MANAGER_H
#define MANAGER_H
#include <stack>
#include <iostream>
#include <string>

#include "../litterales/litterales.h"


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
 * \class FactoryLitterale
 * \brief Création de litterale (Design Patern Factory Method)
*/

class FactoryLitterale : public Factory
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
        Operande* create(std::string value);


};

class FactoryOperateur : public Factory
{

// SINGLETON
    private :
        FactoryOperateur(){}
        FactoryOperateur(const FactoryOperateur& m){}
        FactoryOperateur& operator=(const FactoryOperateur& m){}
        ~FactoryOperateur(){}


        // On utilise une structure, les attributs sont publiques donc pas besoin d'amitie
        struct Handler {
        FactoryOperateur* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
        };

        static Handler handler;

    public:
        static FactoryOperateur& getInstance();
        static void libererInstance();
        Operande* create(std::string value);

};

class Controleur {
private :
    std::stack<Operande*> pile;
public :
    void empiler(Factory& facto, std::string value){pile.push(facto.create(value));}

    void executer();
};


#endif
