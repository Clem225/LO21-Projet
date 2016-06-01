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
        //On cherche le type de la partie réelle
        Entier* compEnt=dynamic_cast<Entier*>(comp->getReal());
        Rationnel* compRat=dynamic_cast<Rationnel*>(comp->getReal());
        Reel* compReal=dynamic_cast<Reel*>(comp->getReal());

        if (compEnt) //La partie reelle du complexe est un entier
        {
            this->operator +(*compEnt);
            comp->setReal(*this);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            compRat->operator +(*this);
            comp->setReal(*this);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            this->operator +(*compReal);
            comp->setReal(*this);
        }
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
        //On cherche le type de la partie réelle
        Entier* compEnt=dynamic_cast<Entier*>(comp->getReal());
        Rationnel* compRat=dynamic_cast<Rationnel*>(comp->getReal());
        Reel* compReal=dynamic_cast<Reel*>(comp->getReal());

        if (compEnt) //La partie reelle du complexe est un entier
        {
            this->operator -(*compEnt);
            comp->setReal(*this);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            this->operator -(*compRat);
            comp->setReal(*this);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            this->operator -(*compReal);
            comp->setReal(*this);
        }
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
        Reel temp(this->getNb()); //Sinon on perd la valeur du reel (this) entre calcul part reelle et calcul part imaginaire

        //On cherche le type de la partie réelle
        Entier* compEnt=dynamic_cast<Entier*>(comp->getReal());
        Rationnel* compRat=dynamic_cast<Rationnel*>(comp->getReal());
        Reel* compReal=dynamic_cast<Reel*>(comp->getReal());

        if (compEnt) //La partie reelle du complexe est un entier
        {
            temp.operator *(*compEnt);
            comp->setReal(temp);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            temp.operator*(*compRat);
            comp->setReal(temp);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            temp.operator*(*compReal);
            comp->setReal(temp);
        }

        //On cherche le type de la partie imaginaire
        Entier* imagEnt=dynamic_cast<Entier*>(comp->getImag());
        Rationnel* imagRat=dynamic_cast<Rationnel*>(comp->getImag());
        Reel* imagReal=dynamic_cast<Reel*>(comp->getImag());

        if (imagEnt) //La partie imaginaire du complexe est un entier
        {
            this->operator *(*imagEnt);
            comp->setImag(*this);
        }
        if (imagRat) //La partie imaginaire du complexe est un rationnel
        {
            this->operator *(*imagRat);
            comp->setImag(*this);
        }
        if (imagReal) //La partie imaginaire du complexe est un réel
        {
            this->operator *(*imagReal);
            comp->setImag(*this);
        }

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





