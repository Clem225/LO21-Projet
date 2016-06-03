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
 * \class Operande
*/

class Operande
{
private :

public:
    /*! \brief Permet d'afficher une opérande*/
    virtual void afficher(std::ostream& f=std::cout) const=0;
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

};

/*!
 * \class Programme
*/
class Programme : public Litterale
{
public :
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
public :
    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);
    Litterale* NEG();
};

/*!
 * \class LitteraleNumerique
*/
class LitteraleNumerique : public ExpressionPart
{
public:
    /*! \brief Renvoi la valeur d'une littérale numérique */
    virtual double getNb() const=0;

};

/*!
 * \class Atome
 */
class Atome : public ExpressionPart
{
private:
    std::string str;
public:
    /*! \brief Constructeur Atome */
    Atome(std::string text): str(text) {}
    Litterale* NEG();
    /*! \brief Renvoie  l'atome*/
    std::string getAtome() const {return str;}
    void afficher(std::ostream& f=std::cout) const {f<<str;}

    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);


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
    /*! \brief Constructeur par defaut - Initialise l'entier à 0 */
    Entier():nb(0){}
    /*! \brief Constructeur de Entier */
    Entier(int n): nb(n) {}
    /*! \brief Opérateur de recopie pour entier */
    Entier* operator=(Entier a);
    Entier* NEG() {nb=-nb; return this;}
    double getNb() const {return nb;}
    /*! \brief Accesseurs en écriture */
    void setValue(int i) {nb=i;}
    void afficher(std::ostream& f=std::cout) const {f<<nb;}

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
    Rationnel* NEG() {numerateur.setValue(-numerateur.getNb());return this;}
    /*! \brief Accesseurs en lecture */
	int getNum() const {return numerateur.getNb();}
    /*! \brief Accesseurs en lecture */
    int getDenom() const {return denominateur.getNb();}
    /*! \brief Renvoie l'inverse */
    Rationnel& getInverse() const {Rationnel* r = new Rationnel(denominateur.getNb(),numerateur.getNb()); return *r;}
    /*! \brief Accesseurs en ecriture */
    void setNum(int e) {numerateur=e;}
    /*! \brief Accesseurs en ecriture */
    void setDenom(int e) {denominateur=e;}
    double getNb() const {double d1 = numerateur.getNb();double d2=denominateur.getNb();return d1/d2;}
    void afficher(std::ostream& f=std::cout) const {f<<getNum()<<"/"<<getDenom();}


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
    void afficher(std::ostream& f=std::cout) const {f<<getNb();}

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
    Complexe* NEG();
    /*! \brief Accesseurs en lecture */
    LitteraleNumerique* getReal() const {return realPart;}
    /*! \brief Accesseurs en lecture */
    LitteraleNumerique* getImag() const {return imagPart;}
    /*! \brief Accesseurs en ecriture */
    void setReal(LitteraleNumerique& lit) {realPart=&lit;}
    /*! \brief Accesseurs en ecriture */
    void setImag(LitteraleNumerique& lit) {imagPart=&lit;}
    void afficher(std::ostream& f=std::cout) const {getReal()->afficher(f); f<<"$"; getImag()->afficher(f);} // A vérif

    /*----------Opérateurs-------------*/

    Litterale* operator+(Litterale& e);
    Litterale* operator-(Litterale& e);
    Litterale* operator*(Litterale& e);
    Litterale* operator/(Litterale& e);
};


#endif
