#ifndef FACTORY_H
#define FACTORY_H

#include "../litterales/litterales.h"

/*!
 * \file factory.h
 * \brief Factorys de creations des litterales et des opérateurs
 * \author Blanquet - Martinache
 * \version 0.1
 */

/*!
 * \class Factory
 * \brief (Abstrait) Création de operateurs ou de litterale (pere des deux factorys)
*/
class Factory
{
public :
    /*! \brief Fonction create qui sera implémenté dans les factorys littérales et opérandes */
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
        /*! \brief Constructeur (SINGLETON) */
        FactoryLitterale(){}
        /*! \brief Constructeur (SINGLETON) */
        FactoryLitterale(const FactoryLitterale& m);
        /*! \brief Recopie (SINGLETON) */
        FactoryLitterale& operator=(const FactoryLitterale& m);
        /*! \brief Destructeur (SINGLETON) */
        virtual ~FactoryLitterale(){}


        /*!
         * \class Handler
         * \brief Gestion du singleton (attribut publique, évite l'amitié)
        */
        struct Handler {
        FactoryLitterale* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
        };

        static Handler handler;

    public:
        /*! \brief (SINGLETON) */
        static FactoryLitterale& getInstance();
        /*! \brief (SINGLETON) */
        static void libererInstance();
        /*! \brief Renvoie un *operande qui pointe vers la bonne littérale */
        Operande* create(std::string value);


};

/*!
 * \class FactoryOperateur
 * \brief Création de operateur (Design Patern Factory Method)
*/

class FactoryOperateur : public Factory
{

// SINGLETON
    private :
        /*! \brief Constructeur (SINGLETON) */
        FactoryOperateur(){}
        /*! \brief Constructeur (SINGLETON) */
        FactoryOperateur(const FactoryOperateur& m);
        /*! \brief Recopie (SINGLETON) */
        FactoryOperateur& operator=(const FactoryOperateur& m);
        /*! \brief Destructeur (SINGLETON) */
        virtual ~FactoryOperateur(){}


        /*!
         * \class Handler
         * \brief Gestion du singleton (attribut publique, évite l'amitié)
        */
        struct Handler {
        FactoryOperateur* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
        };

        static Handler handler;

    public:
        /*! \brief (SINGLETON) */
        static FactoryOperateur& getInstance();
        /*! \brief (SINGLETON) */
        static void libererInstance();
        /*! \brief Renvoie un *operande qui pointe vers le bon opérateur */
        Operande* create(std::string value);

};


#endif // FACTORY_H
