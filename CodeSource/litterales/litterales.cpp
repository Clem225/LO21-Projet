#include "litterales.h"




/*------Classe Entier------*/

Entier& Entier::operator=(Entier a)
{
    // On verifie que ce n'est pas un cas a=a;
    if(this!=&a)
    {
        a.nb=this->getNb();
    }
    return *this;
}

/*------Opérateurs------*/

Litterale& Entier::operator+(Litterale& e) {
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        nb+=ent->getNb();
        return *this;
    }
    if (rat) //c'est un rationnel
    {
        rat->setNum(rat->getNum() + nb*rat->getDenom());
        rat->simplification();
        return *rat;
    }
    if (real) //c'est un reel
    {
        real->setEntiere(real->getEntiere() + nb);
        return *real;
    }
    if (comp) //c'est un complexe
    {
        //On cherche le type de la partie réelle
        Entier* compEnt=dynamic_cast<Entier*>(comp->getReal());
        Rationnel* compRat=dynamic_cast<Rationnel*>(comp->getReal());
        Reel* compReal=dynamic_cast<Reel*>(comp->getReal());

        if (compEnt) //La partie reelle du complexe est un entier
        {
            comp->setReal(Entier(compEnt->getNb() + nb));
            return *comp;
        }
        if (compRat) //C'est un rationnel
        {
            compRat->setNum(compRat->getNum() + nb*compRat->getDenom());
            compRat->simplification();
            comp->setReal(*compRat);
            return *comp;
        }



    }
        

}






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



Reel::Reel(int& e1, int& e2) {
    if (e2<0) throw "Erreur, mantisse<0";
    entiere=e1;
    mantisse=e2;
}

double Reel::getNb() const {
    double temp=mantisse.getNb();
    while (temp>1)
        temp/=10;
    if (entiere.getNb()>0)
        return entiere.getNb()+temp;
    else
        return entiere.getNb()-temp;
}






