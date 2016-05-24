#ifndef LITTERALES_H
#define LITTERALES_H

/*!
 * \file litterales.h
 * \brief Implementation des litterales
 * \author Blanquet - Martinache
 * \version 0.1
 */

#include <iostream>
#include <string>
#include <QString>
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
};

/*!
 * \class Programme
*/
class Programme : public Litterale
{

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

};

/*!
 * \class LitteraleNumerique
*/
class LitteraleNumerique : public ExpressionPart
{

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
    std::string getAtome() const {return tab;}

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
    Entier NEG() {if (nb>0) nb=-nb; return *this;}
    int getNb() const {return nb;}
    void setValue(int i) {nb=i;}
    void afficher(std::ostream& f) const {f<<nb;}

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
	int getNum() const {return numerateur.getNb();}
    int getDenom() const {return denominateur.getNb();}
    Rationnel& getInverse() const {Rationnel* r = new Rationnel(denominateur.getNb(),numerateur.getNb()); return *r;}
    void setNum(int e) {numerateur=e;}
    void setDenom(int e) {denominateur=e;}
    double getNb() const {return numerateur.getNb()/denominateur.getNb();} //Utilité à démontrer
    void afficher(std::ostream& f) const {f<<getNum()<<"/"<<getDenom();}
};

/*!
 * \class Reel
 */
class Reel : public LitteraleNumerique
{
private:
    Entier entiere;
    Entier mantisse;
public:
    // Constructeur. Il faut utiliser des references sinon Reel va appeler le constructeur par defaut de Entier qui n'existe pas !
    Reel(Entier e1, Entier e2):entiere(e1),mantisse(e2){if(e2.getNb()<0) throw LitteraleException("Mantisse negative.");}

    Reel& NEG() {if (entiere.getNb()>0) entiere=entiere.NEG(); return *this;}
    int getEntiere() const {return entiere.getNb();}
    int getMantisse() const {return mantisse.getNb();}
    double getNb() const;
    void setNb(double d);
    void setEntiere(int e) {entiere=e;}
    void setMantisse(int e) {mantisse=e;}
    void afficher(std::ostream& f) const {f<<getNb();}

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
    Complexe(LitteraleNumerique& real, LitteraleNumerique& imag): realPart(&real), imagPart(&imag) {}
    LitteraleNumerique* getReal() const {return realPart;}
    LitteraleNumerique* getImag() const {return imagPart;}
    void setReal(LitteraleNumerique& lit) {realPart=&lit;}
    void setImag(LitteraleNumerique& lit) {imagPart=&lit;}
    void afficher(std::ostream& f) const {getReal()->afficher(f); f<<"$"; getImag()->afficher(f);} // A vérif
};


#endif

