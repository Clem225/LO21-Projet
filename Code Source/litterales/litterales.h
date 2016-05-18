
/*!
 * \file litterales.h
 * \brief Implementation des litterales
 * \author Blanquet - Martinache
 * \version 0.1
 */

#include <iostream>

class Entier {
private:
	int nb;
public:
    // Constructeur
    Entier():nb(0){}
	Entier(unsigned int n): nb(n) {}
    // Transforme l'entier en son opposé.
    // La fonction return *this afin de pouvoir ecrire entier1 = entier2.NEG()
    Entier NEG() {if (nb>0) nb=-nb; return *this;}
	int getNb() const {return nb;}
    void afficher() const {std::cout<<nb;}
    // Constructeur de recopie
    Entier& operator=(Entier a);
};

// La division de deux entiers renvoie un double
double operator/(Entier a, Entier b);


class Rationnel {
private:
	Entier numerateur;
	Entier denominateur;
public:
    // Constructeur (Avec conversion implicite de int e1,e2 en Entier
    Rationnel(int e1, int e2): numerateur(e1), denominateur(e2) {this->simplification();};
	void simplification();
	int getNum() const {return numerateur.getNb();}
	int getDenom() const {return denominateur.getNb();}
    double getNb() const {return numerateur/denominateur;}
    void afficher() const {std::cout<<getNum()<<"/"<<getDenom();}
};


class Reel {
private:
    Entier entiere;
    Entier mantisse;
public:
    // Constructeur. Il faut utiliser des references sinon Reel va appeler le constructeur par defaut de Entier qui n'existe pas !
    Reel(int& e1, int& e2);
    // Transforme le reel en son opposé.
    // La fonction return *this afin de pouvoir ecrire reel1 = reel2.NEG()
    Reel NEG() {if (entiere.getNb()>0) entiere=entiere.NEG(); return *this;}
	void afficher() const {/*.....*/;}

};



//Rationnel operator/(int e1, int e2);
//Reel operator.(int e1, int e2);

