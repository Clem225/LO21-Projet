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





/*------Classe Entier------*/

Litterale& Entier::operator+(Litterale& e) {
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp))
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

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
            Entier* e= new Entier(compEnt->getNb() + nb);
            comp->setReal(*e);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            compRat->setNum(compRat->getNum() + nb*compRat->getDenom());
            compRat->simplification();
            comp->setReal(*compRat);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            compReal->setEntiere(compReal->getEntiere() + nb);
            comp->setReal(*compReal);
        }

        return *comp;
    }
}



Litterale& Entier::operator-(Litterale& e)
{
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        nb-=ent->getNb();
        return *this;
    }
    if (rat) //c'est un rationnel
    {
        rat->setNum(nb*rat->getDenom() - rat->getNum());
        rat->simplification();
        return *rat;
    }
    if (real) //c'est un reel
    {
        real->setEntiere(nb - real->getEntiere());
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
            Entier* e= new Entier(nb - compEnt->getNb());
            comp->setReal(*e);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            compRat->setNum(nb*compRat->getDenom() - compRat->getNum());
            compRat->simplification();
            comp->setReal(*compRat);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            compReal->setEntiere(nb - compReal->getEntiere());
            comp->setReal(*compReal);
        }

        return *comp;
    }

}



Litterale& Entier::operator*(Litterale& e) {
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        nb*=ent->getNb();
        return *this;
    }
    if (rat) //c'est un rationnel
    {
        rat->setNum(nb*rat->getNum());
        rat->simplification();
        return *rat;
    }
    if (real) //c'est un reel
    {
        real->setEntiere(nb * real->getEntiere());
        double temp=real->getMantisse();
        while (temp>1)
            temp/=10;
        temp*=nb;
        while (temp>=1)
        {
            real->setEntiere(real->getEntiere() + 1);
            temp-=1;
        }
        real->setMantisse(temp);
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
            Entier* e= new Entier(nb * compEnt->getNb());
            comp->setReal(*e);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            compRat->setNum(nb*compRat->getNum());
            compRat->simplification();
            comp->setReal(*compRat);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            compReal->setEntiere(nb * compReal->getEntiere());
            double temp=compReal->getMantisse();
            while (temp>1)
                temp/=10;
            temp*=nb;
            while (temp>=1)
            {
                compReal->setEntiere(compReal->getEntiere() + 1);
                temp-=1;
            }
            compReal->setMantisse(temp);

            comp->setReal(*compReal);
        }

        return *comp;
    }
}



/*Litterale& Entier::operator/(Litterale& e) {
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        if (ent->getNb()==0)
            throw "Erreur : division par zero";
        if (nb % ent->getNb()==0) // Si le reste de la division est zéro
        {
            nb/=ent->getNb();
            return *this;
        }
        else
        {
            Rationnel* r = new Rationnel(nb,ent->getNb());
            return *r;
        }
    }
    if (rat) //c'est un rationnel
    {
        return this->operator*(rat->getInverse()); // On multiplie par l'inverse plutot que diviser
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        double res = (double nb / d);
        real->setNb(res);
        return *real;
    }
    if (comp) //c'est un complexe
    {
        Entier* compImag=dynamic_cast<Entier*>(comp->getImag));
        if (compImag)
            if (compImag->getNb()==0)
                nb/=
        //On cherche le type de la partie réelle
        Entier* compEnt=dynamic_cast<Entier*>(comp->getReal());
        Rationnel* compRat=dynamic_cast<Rationnel*>(comp->getReal());
        Reel* compReal=dynamic_cast<Reel*>(comp->getReal());

        if (compEnt) //La partie reelle du complexe est un entier
        {
            comp->setReal(Entier(nb * compEnt->getNb()));
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            compRat->setNum(nb*compRat->getNum());
            compRat->simplification();
            comp->setReal(*compRat);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            Entier* e= new Entier(nb * compEnt->getNb());
            comp->setReal(*e);
            double temp=compReal->getMantisse();
            while (temp>1)
                temp/=10;
            temp*=nb;
            while (temp>=1)
            {
                compReal->setEntiere(compReal->getEntiere() + 1);
                temp-=1;
            }
            compReal->setMantisse(temp);

            comp->setReal(*compReal);
        }

        return *comp;
    }
}*/
