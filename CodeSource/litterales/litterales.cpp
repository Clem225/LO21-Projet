#include "litterales.h"

Entier& Entier::operator=(Entier a)
{
    // On verifie que ce n'est pas un cas a=a;
    if(this!=&a)
    {
        a.nb=this->getNb();
    }
    return *this;
}

template<typename Type> Type operator/(Entier a, Entier b)
{
    // si le numerateur est 0, le denominateur prend la valeur 1
    if (a.getNb()==0) b.setValue(1);
    if (b.getNb()==0) throw "Erreur, division par zero";
    /* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le numerateur et le denominateur */
    int tempa =a.getNb(), tempb=b.getNb();
    // on ne travaille qu’avec des valeurs positives...
    if (tempa<0) tempa=-tempa; if (tempb<0) tempb=-tempb;
    while(tempa!=tempb){ if (tempa>tempb) tempa=tempa-tempb; else tempb=tempb-tempa; }
    // on divise le numerateur et le denominateur par le PGCD=a
    a.setValue(a.getNb()/tempa); b.setValue(b.getNb()/tempa);
    // si le denominateur est négatif, on fait passer le signe - au denominateur
    if (b.getNb()<0) { b.setValue(-b.getNb()); a.setValue(-a.getNb()); }

    if (b==1) {delete b; return a;}
    else return Rationnel(a,b);
}


Reel::Reel(int& e1, int& e2)
{
    if (e2==0){}
		//cast vers Entier
	entiere=e1;
	mantisse=e2;
}



