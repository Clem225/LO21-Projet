#include "litterales.h"
#include "operateurs.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <limits>



/*------Classe rationnel------*/

Entier Rationnel::simplification() {
    if (getNum()!=0) {
        /* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
        Denominateur (PGCD) entre le num et le denominateur */
        int num=getNum(), denom=getDenom();
        // on ne travaille qu’avec des valeurs positives...
        if (num<0) num=-num;
        if (denom<0) denom=-denom;
        while(num!=denom)
        {
            if (num>denom) num=num-denom; else denom=denom-num;
        }
        // on divise le num et le denom par le PGCD=a
        setNum(getNum()/num); setDenom(getDenom()/num);
        // si le denom est négatif, on fait passer le signe - au denom
        if (getDenom()<0) { setDenom(-getDenom()); setNum(-getNum()); }

        //Test pour tranformation en Entier. On ne retourne une valeur que si c'est tranformable en entier
        if ((numerateur.getNb()==0) || (denominateur.getNb()==1))
            return Entier(numerateur.getNb());
    }
    else
    {
        setNum(0);
        setDenom(0);
    }
}

// Constructeur rationnel
Rationnel::Rationnel(int e1, int e2) {
    if (e2==0) throw "Erreur, division par zero";
    numerateur=e1;
    denominateur=e2;
    simplification();
}




/*------Classe Reel------*/



int Reel::getEntiere() const {
    long double ent;
    modfl(nb,&ent);
    return ent;
}


double Reel::getMantisse() const {
    long double ent,v;
    v=modfl(nb,&ent);
    return v;
}


void Reel::setEntiere(const Entier& e) {
    long double ent,v;
    v=modfl(nb,&ent);
    ent=e.getNb();
    ent+=v;
    nb=ent;
}

void Reel::setMantisse(const double &e)
{
    long double ent,v;
    v=modfl(nb,&ent);
    v=e;
    ent+=v;
    nb=ent;
}




