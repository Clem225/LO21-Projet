#ifndef FACTORY_H
#define FACTORY_H

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

/*!
 * \class FactoryOperateur
 * \brief Création de operateur (Design Patern Factory Method)
*/

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


#endif // FACTORY_H
