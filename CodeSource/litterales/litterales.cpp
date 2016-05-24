#include "litterales.h"


/*------Classe rationnel------*/

Entier Rationnel::simplification() {
    /* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le num et le denominateur */
    int num=getNum(), denom=getDenom();
    // on ne travaille qu’avec des valeurs positives...
    if (num<0) num=-num; if (denom<0) denom=-denom;
    while(num!=denom){ if (num>denom) num=num-denom; else denom=denom-num; }
    // on divise le num et le denom par le PGCD=a
    setNum(getNum()/num); setDenom(getDenom()/num);
    // si le denom est négatif, on fait passer le signe - au denom
    if (getDenom()<0) { setDenom(-getDenom()); setNum(-getNum()); }

    //Test pour tranformation en Entier. On ne retourne une valeur que si c'est tranformable en entier
    if ((numerateur.getNb()==0) || (denominateur.getNb()==1))
        return Entier(numerateur.getNb());
}



Rationnel::Rationnel(int e1, int e2) {
    if (e2==0) throw "Erreur, division par zero";
    numerateur=e1;
    denominateur=e2;
    simplification();
}




/*------Classe Réel------*/

/*
    double temp=mantisse.getNb();
    while (temp>1)
        temp/=10;
    if (entiere.getNb()>0)
        return entiere.getNb()+temp;
    else
        return entiere.getNb()-temp;
}

*/




