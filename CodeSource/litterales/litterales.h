#ifndef LITTERALES_H
#define LITTERALES_H

/*!
 * \file litterales.h
 * \brief Implementation des litterales
 * \author Blanquet - Martinache
 * \version 0.1
 */

#include <iostream>
#include "../manager/manager.h"

class Operande
{

};

/*!
 * \class Operateur
*/

class Operateur : public Operande
{

};

/*!
 * \class Litterale
*/

class Litterale : public Operande
{
public:
    virtual void afficher(std::ostream& f=std::cout) const=0;
    virtual Litterale& NEG() =0;
    virtual Litterale& operator+(Litterale& e) =0;
};

/*!
 * \class Programme
*/
class Programme : public Litterale
{
public :
        Litterale& operator+(Litterale& e);
        Litterale& NEG();
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
        Litterale& operator+(Litterale& e);
        Litterale& NEG();
};

/*!
 * \class LitteraleNumerique
*/
class LitteraleNumerique : public ExpressionPart
{
public:
    virtual double getNb() const=0;

};

/*!
 * \class Atome
 */
class Atome : public ExpressionPart
{
private:
    std::string tab;
public:
    Atome(std::string text): tab(text) {}
    Litterale& NEG();
    std::string getAtome() const {return tab;}
    void afficher(std::ostream& f=std::cout) const {f<<tab;}

    Litterale& operator+(Litterale& e);


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
    Entier():nb(0){}
    Entier(int n): nb(n) {}
    Entier& operator=(Entier a);
    Entier& NEG() {nb=-nb; return *this;}
    double getNb() const {return nb;}
    void setValue(int i) {nb=i;}
    void afficher(std::ostream& f=std::cout) const {f<<nb;}

    /*----------Opérateurs-------------*/

    Litterale& operator+(Litterale& e);
    Litterale& operator-(Litterale& e);
    Litterale& operator*(Litterale& e);
    Litterale& operator/(Litterale& e);

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
    Entier simplification();
    Rationnel(int e1, int e2);
    Rationnel& NEG() {numerateur.setValue(-numerateur.getNb());return *this;}
	int getNum() const {return numerateur.getNb();}
    int getDenom() const {return denominateur.getNb();}
    Rationnel& getInverse() const {Rationnel* r = new Rationnel(denominateur.getNb(),numerateur.getNb()); return *r;}
    void setNum(int e) {numerateur=e;}
    void setDenom(int e) {denominateur=e;}
    double getNb() const {double d1 = numerateur.getNb();double d2=denominateur.getNb();return d1/d2;}
    void afficher(std::ostream& f=std::cout) const {f<<getNum()<<"/"<<getDenom();}


    /*----------Opérateurs-------------*/

    Litterale& operator+(Litterale& e);
    Litterale& operator-(Litterale& e);
    Litterale& operator*(Litterale& e);
    Litterale& operator/(Litterale& e);
};

/*!
 * \class Reel
 */
class Reel : public LitteraleNumerique
{
private:
    double nb;
public:
    // Constructeur. Il faut utiliser des references sinon Reel va appeler le constructeur par defaut de Entier qui n'existe pas !
    Reel(double d):nb(d) {}

    Reel& NEG() {nb=-nb; return *this;}
    int getEntiere() const;
    double getMantisse() const;
    double getNb() const {return nb;}
    void setNb(long double d) {nb=d;}
    void setEntiere(const Entier& e);
    void setMantisse(const double& e);
    void afficher(std::ostream& f=std::cout) const {f<<getNb();}

    /*----------Opérateurs-------------*/

    Litterale& operator+(Litterale& e);
    Litterale& operator-(Litterale& e);
    Litterale& operator*(Litterale& e);
    Litterale& operator/(Litterale& e);

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
    Complexe(LitteraleNumerique* real, LitteraleNumerique* imag): realPart(real), imagPart(imag) {}
    Complexe& NEG();
    LitteraleNumerique* getReal() const {return realPart;}
    LitteraleNumerique* getImag() const {return imagPart;}
    void setReal(LitteraleNumerique& lit) {realPart=&lit;}
    void setImag(LitteraleNumerique& lit) {imagPart=&lit;}
    void afficher(std::ostream& f=std::cout) const {getReal()->afficher(f); f<<"$"; getImag()->afficher(f);} // A vérif

    /*----------Opérateurs-------------*/

    Litterale& operator+(Litterale& e);
    Litterale& operator-(Litterale& e);
    Litterale& operator*(Litterale& e);
    /*Litterale& operator/(Litterale& e);*/
};


#endif

