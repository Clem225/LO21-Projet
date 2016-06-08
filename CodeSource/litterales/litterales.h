#ifndef LITTERALES_H
#define LITTERALES_H

#include <iostream>

/*!
 * \file litterales.h
 * \brief Implementation des litterales
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
    /*! \brief Constructeur */
    LitteraleException(const std::string& str):info(str){}
    /*! \brief Renvoie les informations sur l'erreur */
    std::string getInfo() const { return info; }
};


/*!
 * \class Operande
*/
class Operande
{
private :

public:
    /*! \brief Permet d'afficher une opérande*/
    void afficher(std::ostream& f=std::cout){f<<toString();}
    virtual std::string toString() const =0;
};

/*!
 * \class Litterale
*/
class Litterale : public Operande
{
public:
    /*! \brief Renvoi l'opposé d'une littérale*/
    virtual Litterale* NEG() =0;
        /*! \brief Operateur entre littérale */
    virtual Litterale* operator+(Litterale& e) =0;
        /*! \brief Operateur entre littérale */
    virtual Litterale* operator-(Litterale& e) =0;
        /*! \brief Operateur entre littérale */
    virtual Litterale* operator*(Litterale& e) =0;
        /*! \brief Operateur entre littérale */
    virtual Litterale* operator/(Litterale& e) =0;

    /*! \brief Renvoi la valeur d'une littérale numérique */
    virtual double getNb() const=0;

};

/*!
 * \class Programme
*/
class Programme : public Litterale
{
public :
    // COnstructeur de recopie à faire
    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);
    Litterale* NEG();
};

/*!
 * \class ExpressionPart
 */
class ExpressionPart : public Litterale
{

};

/*!
 * \class Expression
*/
class Expression : public Litterale
{
    std::string str;
public :
    Expression(std::string s): str(s) {};
    //void afficher(std::ostream& f=std::cout) const {f<<str;}
    std::string toString() const {return str;}
    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);
    Litterale* NEG();
    std::string getExpr() const {return str;}


    double getNb() const;
};

/*!
 * \class LitteraleNumerique
*/
class LitteraleNumerique : public ExpressionPart
{
public:


};

/*!
 * \class Atome
 */
class Atome : public ExpressionPart
{
private:
    std::string str;
    Litterale* link;
public:
    /*! \brief Constructeur Atome */
    Atome(std::string text, Litterale* p=nullptr): str(text), link(p) {}
    /*! \brief Constructeur de recopie */
    Atome(const Atome& atom):str(atom.getAtome()){}
    /*! \brief Renvoie  l'atome*/
    std::string getAtome() const {return str;}
    /*! \brief Renvoie  la variable ou le programme auquel est lie l'atome*/
    Litterale* getLink() const {return link;}

    //void afficher(std::ostream& f=std::cout) const {f<<str;}
    std::string toString() const {return str;}

    /*INUTILE, JUSTE POUR EVITER ABSTRAIT*/
    Litterale* NEG();
    double getNb() const;
    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);
};



/*------Classes de MANAGER------*/

class AtomeManager {
private:
    Atome** atoms;
    unsigned int nb;
    unsigned int nbMax;
    struct Handler{
        AtomeManager* instance;
        Handler():instance(nullptr){}
        // destructeur appelé à la fin du programme
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    AtomeManager(): atoms(nullptr), nb(0), nbMax(0) {}
    Atome* addAtome(Atome* a);
    void delAtome(Atome* a);
    void agrandissementCapacite();
    static AtomeManager& getInstance();
    static void libererInstance();

    //ITERATOR
    class Iterator {
        friend class AtomeManager;
        Atome** currentExp;
        unsigned int nbRemain;
        Iterator(Atome** u, unsigned nb):currentExp(u),nbRemain(nb){}
    public:
        Iterator():currentExp(nullptr),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw LitteraleException("error, next on an iterator which is done");
            nbRemain--;
            currentExp++;
        }
        Atome& current() const {
            if (isDone())
                throw LitteraleException("error, indirection on an iterator which is done");
            return **currentExp;
        }
    };
   Iterator getIterator() { return Iterator(atoms,nb); }
};


/*----------------------Classes de littérales numériques-------------------------*/


/*!
 * \class Entier
 */
class Entier : public LitteraleNumerique
{
private:
    int nb;
public:
    //void afficher(std::ostream& f=std::cout) const {f<<nb;}
    std::string toString() const {return std::to_string(nb);}

    /*! \brief Constructeur par defaut - Initialise l'entier à 0 */
    Entier():nb(0){}
    /*! \brief Constructeur de Entier */
    Entier(int n): nb(n) {}
    /*! \brief Constructeur de recopie */
    Entier(const Entier& ent):nb(ent.getNb()){}

    /*! \brief Opérateur de recopie pour entier */
    Entier* operator=(Entier a);

    Entier* NEG() {nb=-nb; return this;}

    double getNb() const {return nb;}
    /*! \brief Accesseurs en écriture */
    Entier* setValue(int i) {nb=i;return this;}

    /*----------Opérateurs-------------*/

    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);

};


/*!
 * \class Rationnel
 */
class Rationnel : public LitteraleNumerique
{
private:
    Entier numerateur;
    Entier denominateur;
public:
    /*! \brief Simplification d'un rationnel */
    Entier simplification();

    /*! \brief Constructeur : e1 = numérateur, e2 = denominateur */
    Rationnel(int e1, int e2);
    /*! \brief Constructeur de recopie */
    Rationnel(const Rationnel& rat):numerateur(rat.getNum()),denominateur(rat.getDenom()){}

    Rationnel* NEG() {numerateur.setValue(-numerateur.getNb());return this;}

    /*! \brief Accesseurs en lecture */
    int getNum() const {return numerateur.getNb();}
    /*! \brief Accesseurs en lecture */
    int getDenom() const {return denominateur.getNb();}

    /*! \brief Renvoie l'inverse */
    Rationnel& getInverse() const {Rationnel* r = new Rationnel(denominateur.getNb(),numerateur.getNb()); return *r;}

    /*! \brief Accesseurs en ecriture */
    void setNum(const int e) {numerateur=e;}
    /*! \brief Accesseurs en ecriture */
    void setDenom(const int e) {denominateur=e;}

    double getNb() const {double d1 = numerateur.getNb();double d2=denominateur.getNb();return d1/d2;}
    //void afficher(std::ostream& f=std::cout) const {f<<getNum()<<"/"<<getDenom();}
    std::string toString() const {return std::to_string(numerateur.getNb())+"/"+std::to_string(denominateur.getNb());}

    /*----------Opérateurs-------------*/

    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);
};

/*!
 * \class Reel
 */
class Reel : public LitteraleNumerique
{
private:
    double nb;
public:
    /*! \brief Constructeur */
    Reel(double d):nb(d) {}
    /*! \brief Constructeur de recopie */
    Reel(const Reel& rel):nb(rel.getNb()){}

    Reel* NEG() {nb=-nb; return this;}
    /*! \brief Accesseurs en lecture */
    int getEntiere() const;
    /*! \brief Accesseurs en lecture */
    double getMantisse() const;
    /*! \brief Accesseurs en lecture */
    double getNb() const {return nb;}
    /*! \brief Accesseurs en ecriture */
    void setNb(long double d) {nb=d;}
    /*! \brief Accesseurs en ecriture */
    void setEntiere(const Entier& e);
    /*! \brief Accesseurs en ecriture */
    void setMantisse(const double& e);
    //void afficher(std::ostream& f=std::cout) const {f<<getNb();}
    std::string toString() const {return std::to_string(nb);}

    /*----------Opérateurs-------------*/

    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);

};

/*!
 * \class Complexe
 */
class Complexe : public ExpressionPart
{
private:
    LitteraleNumerique* realPart; //On ne connait pas le type exact. C'est soit un reel, soit un rationnel, soit un entier.
    LitteraleNumerique* imagPart;
public:
    /*! \brief Constructeur */
    Complexe(LitteraleNumerique* real, LitteraleNumerique* imag): realPart(real), imagPart(imag) {}
    /*! \brief Constructeur de recopie */
    Complexe(const Complexe& comp):realPart(comp.getReal()),imagPart(comp.getImag()){}

    Complexe* NEG();
    /*! \brief Accesseurs en lecture */
    LitteraleNumerique* getReal() const {return realPart;}
    /*! \brief Accesseurs en lecture */
    LitteraleNumerique* getImag() const {return imagPart;}
    /*! \brief Accesseurs en ecriture */
    void setReal(LitteraleNumerique& lit) {realPart=&lit;}
    /*! \brief Accesseurs en ecriture */
    void setImag(LitteraleNumerique& lit) {imagPart=&lit;}
    //void afficher(std::ostream& f=std::cout) const {getReal()->afficher(f); f<<"$"; getImag()->afficher(f);}
    std::string toString() const {return std::to_string(realPart->getNb())+"$"+std::to_string(imagPart->getNb());}
    double getNb() const {return 0;} //juste pour empeche l'abstrait

    /*----------Opérateurs-------------*/

    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);
};


#endif
