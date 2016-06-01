#include "operateurs.h"



Litterale& Reel::operator+(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp))
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        return ent->operator +(*this);
    }
    if (rat) //c'est un rationnel
    {
        rat->operator +(*this);
        return *this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        nb+=d;
        return *this;
    }
    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(   this->operator +(*comp->getReal())   ));
        return *comp;
    }
}



Litterale& Reel::operator-(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp))
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        ent->operator -(*this);
        this->setNb(-1*this->getNb()); //On échange le signe car opération dans le mauvais sens
        return *this;
    }
    if (rat) //c'est un rationnel
    {
        rat->operator -(*this);
        this->setNb(-1*this->getNb()); //On échange le signe car opération dans le mauvais sens
        return *this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d= nb-d;
        setNb(d);
        return *this;
    }
    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(   this->operator -(*comp->getReal())   ));
        return *comp;
    }
}



Litterale& Reel::operator*(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        return ent->operator*(*this);
    }
    if (rat) //c'est un rationnel
    {
        rat->operator *(*this);
        return *this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d = nb * d;
        setNb(d);
        return *this;
    }
    if (comp) //c'est un complexe
    {
        Reel* newr = new Reel(this->getNb());
        comp->setReal(dynamic_cast<LitteraleNumerique&>(   this->operator *(*comp->getReal())   ));
        comp->setImag(dynamic_cast<LitteraleNumerique&>(   newr->operator *(*comp->getImag())   ));
        return *comp;
    }

}



Litterale& Reel::operator/(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        double d = ent->getNb();
        d = getNb() /d;
        setNb(d);
        return *this;
    }
    if (rat) //c'est un rationnel
    {
        double d = rat->getNb();
        d = getNb() / d;
        setNb(d);
        return *this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d = getNb() / d;
        setNb(d);
        return *this;
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
            this->operator *(*compEnt);
            comp->setReal(*this);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            this->operator*(*compRat);
            comp->setReal(*this);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            this->operator*(*compReal);
            comp->setReal(*this);
        }
        return *comp;
    }*/

}





