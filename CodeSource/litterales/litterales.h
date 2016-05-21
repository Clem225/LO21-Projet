
/*!
 * \file litterales.h
 * \brief Implementation des litterales
 * \author Blanquet - Martinache
 * \version 0.1
 */

#include <iostream>

/*!
 * \class Litterale
*/
class Litterale {
public:
    virtual void afficher(std::ostream& f) const=0;
};

/*!
 * \class ExpressionPart
 */
class ExpressionPart : public Litterale {

};

/*!
 * \class Expression
*/
class Expression : public Litterale {
private:
    ExpressionPart** tab;
};

/*!
 * \class LitteraleNumerique
*/
class LitteraleNumerique : public ExpressionPart {

};

/*!
 * \class Atome
 */
class Atome : public ExpressionPart {

};

/*!
 * \class Entier
 */
class Entier : public LitteraleNumerique {
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

};


/*!
 * \class Rationnel
 */
class Rationnel : public LitteraleNumerique {
private:
	Entier numerateur;
	Entier denominateur;
public:
    // Constructeur (Avec conversion implicite de int e1,e2 en Entier
    Rationnel(int e1, int e2): numerateur(e1), denominateur(e2) {};
	int getNum() const {return numerateur.getNb();}
	int getDenom() const {return denominateur.getNb();}
    double getNb() const {return numerateur.getNb()/denominateur.getNb();} //Utilité à démontrer
    void afficher(std::ostream& f) const {f<<getNum()<<"/"<<getDenom();}
};


/*!
 * \class Reel
 */
class Reel : public LitteraleNumerique {
private:
    Entier entiere;
    Entier mantisse;
public:
    // Constructeur. Il faut utiliser des references sinon Reel va appeler le constructeur par defaut de Entier qui n'existe pas !
    Reel(int& e1, int& e2);
    Reel NEG() {if (entiere.getNb()>0) entiere=entiere.NEG(); return *this;}
    double getNb() const;
    int getEntiere() const {return entiere.getNb();} //Utilité à démontrer
    int getMantisse() const {return mantisse.getNb();} //Utilité à démontrer
    void afficher(std::ostream& f) const {f<<getNb();}

};

/*!
 * \class Complexe
 */

class Complexe : public ExpressionPart {
private:
    LitteraleNumerique* realPart; //On ne connait pas le type exact. C'est soit un reel, soit un rationnel, soit un entier.
    LitteraleNumerique* imagPart;
public:



};


template<typename Type> Type operator/(Entier e1, Entier e2); // A vérifier par la suite
