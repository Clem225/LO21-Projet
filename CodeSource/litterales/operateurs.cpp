#include "operateurs.h"

Entier& Entier::operator=(Entier a)
{
    // On verifie que ce n'est pas un cas a=a;
    if(this!=&a)
    {
        a.nb=this->getNb();
    }
    return *this;
}

bool operator==(const Entier& a, const Entier& b)
{
    return a.getNb()==b.getNb();
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
    if (tempa<0) tempa=-tempa;
    if (tempb<0) tempb=-tempb;
    while(tempa!=tempb){ if (tempa>tempb) tempa=tempa-tempb; else tempb=tempb-tempa; }
    // on divise le numerateur et le denominateur par le PGCD=a
    a.setValue(a.getNb()/tempa); b.setValue(b.getNb()/tempa);
    // si le denominateur est négatif, on fait passer le signe - au denominateur
    if (b.getNb()<0) { b.setValue(-b.getNb()); a.setValue(-a.getNb()); }

    //if (b==1) {delete b; return a;}
    //else return Rationnel(a,b);
}

// Attention, je pense que tu peux caster un entier en reel... A voir...
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
            //comp->setReal(Entier(compEnt->getNb() + nb));
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
