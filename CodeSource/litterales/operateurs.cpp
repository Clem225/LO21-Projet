#include "operateurs.h"
#include <math.h>
#include <limits>
#include <iostream>

/* ---------------- DOUBLE --------------- */


// Compare deux double
bool areSame(long double a, long double b)
{
    return fabs(a - b) < std::numeric_limits<double>::epsilon() ;
}

/* ---------------- ENTIER --------------- */

// Operateur d'affectation
Entier& Entier::operator=(Entier a)
{
    // On verifie que ce n'est pas un cas a=a;
    if(this!=&a)
    {
        nb=a.getNb();
    }

    return *this;
}

// Operateur de comparaison
bool operator==(const Entier& a, const Entier& b)
{
    return a.getNb()==b.getNb();
}


/* ---------------- TEST GREG --------------- */

Litterale& Rationnel::operator+(Litterale& e)
{

}

Litterale& Reel::operator+(Litterale& e)
{

}
Litterale& Complexe::operator+(Litterale& e)
{

}
Litterale& Programme::operator+(Litterale& e)
{

}
Litterale& Expression::operator+(Litterale& e)
{

}
Litterale& Atome::operator+(Litterale& e)
{

}
/* ---------------- TEMPLATE --------------- */


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
        double d= real->getNb();
        double nb2=nb;
        double result = nb2-d;
        real->setNb(result);
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
            compReal->setNb(nb - compReal->getNb());
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
        double d = real->getNb();
        d = nb * d;
        real->setNb(d);
        return  *real;
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



Litterale& Entier::operator/(Litterale& e) {
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
        double res = nb / d;
        real->setNb(res);
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
            Reel* r= new Reel(nb / compEnt->getNb());
            comp->setReal(*r);
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


        //On cherche la partie imaginaire
        Entier* compImEnt=dynamic_cast<Entier*>(comp->getImag());
        Rationnel* compImRat=dynamic_cast<Rationnel*>(comp->getImag());
        Reel* compImReal=dynamic_cast<Reel*>(comp->getImag());

        if (compImEnt) //Si la partie imaginaire est entière
        {
            if (*compImEnt==0) // Et qu'elle est nulle
                return *(comp->getReal()); //On renvoie uniquement la partie réelle
            else
            {
                double d = nb / compImEnt->getNb();
                Reel* r= new Reel(d);
                comp->setImag(*r);
            }
        }
        if (compImRat) //Si la partie imaginaire est rationnelle
        {
            int temp = compImRat->getDenom();
            compImRat->setDenom(compImRat->getNum());
            compImRat->setNum(nb*temp);
            comp->setImag(*compImRat);
        }
        if (compImReal) //Si la partie imaginaire est reelle
        {
            compImReal->setNb(nb / compImReal->getNb());
            comp->setImag(*compImReal);
        }

        return *comp;
    }
}
