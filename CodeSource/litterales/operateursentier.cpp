#include "operateurs.h"
#include "../litterales/litterales.h"



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
        comp->setReal(dynamic_cast<LitteraleNumerique&>(   this->operator +(*comp->getReal())   ));
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
        comp->setReal(dynamic_cast<LitteraleNumerique&>(   this->operator -(*comp->getReal())   ));
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
        //Test si ça donne un entier
        if ( (rat->getDenom()==1) || (rat->getNum()==0) )
        {
            Entier* e = new Entier(rat->getNum());
            return *e;
        }
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
        comp->setReal(dynamic_cast<LitteraleNumerique&>(   this->operator *(*comp->getReal())   ));
        comp->setImag(dynamic_cast<LitteraleNumerique&>(   this->operator *(*comp->getImag())   ));
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
        int e1 = nb;
        int e2 = ent->getNb();
        if (e1 % e2==0) // Si le reste de la division est zéro
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
    /* A FAIRE PLUS TARD
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
            double n = nb;
            double res = n / compReal->getNb();
            Reel* r= new Reel(res);
            comp->setReal(*r);
        }


        //On cherche la partie imaginaire
        Entier* compImEnt=dynamic_cast<Entier*>(comp->getImag());
        Rationnel* compImRat=dynamic_cast<Rationnel*>(comp->getImag());
        Reel* compImReal=dynamic_cast<Reel*>(comp->getImag());

        if (compImEnt) //Si la partie imaginaire est entière
        {
            if (compImEnt->getNb()==0) // Et qu'elle est nulle
                return *(comp->getReal()); //On renvoie uniquement la partie réelle
            else
            {
                Rationnel* r = new Rationnel(nb,compImEnt->getNb());
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
            double n = nb;
            double res= n / compImReal->getNb();
            compImReal->setNb(res);
            comp->setImag(*compImReal);
        }

        return *comp;
    }*/
}
