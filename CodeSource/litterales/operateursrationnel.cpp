#include "operateurs.h"








Litterale& Rationnel::operator+(Litterale& e){
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
        int num=rat->getNum(), denom=rat->getDenom();
        //Mise sous forme de dénominateur commun
        rat->setNum(num*denominateur.getNb());
        rat->setDenom(denom*denominateur.getNb());
        numerateur.setValue(numerateur.getNb()*denom);
        denominateur.setValue(denominateur.getNb()*denom);
        //Addition des numérateurs puis simplification
        numerateur.setValue(numerateur.getNb()+rat->getNum());
        simplification();
        //Test si ça donne un entier
        if ( (denominateur.getNb()==1) || (numerateur.getNb()==0) )
        {
            Entier* e = new Entier(numerateur.getNb());
            return *e;
        }
        return *this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d+=this->getNb();
        real->setNb(d);
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
            this->operator +(*compEnt);
            comp->setReal(*this);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            int num=compRat->getNum(), denom=compRat->getDenom();
            //Mise sous forme de dénominateur commun
            compRat->setNum(num*denominateur.getNb());
            compRat->setDenom(denom*denominateur.getNb());
            numerateur.setValue(numerateur.getNb()*denom);
            denominateur.setValue(denominateur.getNb()*denom);
            //Addition des numérateurs puis simplification
            numerateur.setValue(numerateur.getNb()+compRat->getNum());
            simplification();
            //Test si ça donne un entier
            if ( (denominateur.getNb()==1) || (numerateur.getNb()==0) )
            {
                Entier* e = new Entier(numerateur.getNb());
                comp->setReal(*e);
            }
            else
            {
            compRat->setNum(this->getNum());
            compRat->setDenom(this->getDenom());
            comp->setReal(*compRat);
            }
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            this->operator +(*compReal);
            comp->setReal(*compReal);
        }
        return *comp;
    }
}

Litterale& Rationnel::operator-(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp))
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        ent->operator -(*this);
        numerateur.setValue(-1*numerateur.getNb()); //On échange le signe car opération dans le mauvais sens
        return *this;
    }
    if (rat) //c'est un rationnel
    {
        int num=rat->getNum(), denom=rat->getDenom();
        //Mise sous forme de dénominateur commun
        rat->setNum(num*denominateur.getNb());
        rat->setDenom(denom*denominateur.getNb());
        numerateur.setValue(numerateur.getNb()*denom);
        denominateur.setValue(denominateur.getNb()*denom);
        //Soustraction des numérateurs puis simplification
        numerateur.setValue(numerateur.getNb()-rat->getNum());
        simplification();
        //Test si ça donne un entier
        if ( (denominateur.getNb()==1) || (numerateur.getNb()==0) )
        {
            Entier* e = new Entier(numerateur.getNb());
            return *e;
        }
        return *this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d=this->getNb()-d;
        real->setNb(d);
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
            this->operator -(*compEnt);
            comp->setReal(*this);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            int num=compRat->getNum(), denom=compRat->getDenom();
            //Mise sous forme de dénominateur commun
            compRat->setNum(num*denominateur.getNb());
            compRat->setDenom(denom*denominateur.getNb());
            numerateur.setValue(numerateur.getNb()*denom);
            denominateur.setValue(denominateur.getNb()*denom);
            //Addition des numérateurs puis simplification
            numerateur.setValue(numerateur.getNb()-compRat->getNum());
            simplification();
            //Test si ça donne un entier
            if ( (denominateur.getNb()==1) || (numerateur.getNb()==0) )
            {
                Entier* e = new Entier(numerateur.getNb());
                comp->setReal(*e);
            }
            else
            {
            compRat->setNum(this->getNum());
            compRat->setDenom(this->getDenom());
            comp->setReal(*compRat);
            }
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            this->operator -(*compReal);
            comp->setReal(*compReal);
        }
        return *comp;
    }
}

Litterale& Rationnel::operator*(Litterale& e){
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
        numerateur.setValue(getNum()*rat->getNum());
        denominateur.setValue(getDenom()*rat->getDenom());
        simplification();
        //Test si entier
        if ((numerateur.getNb()==0)||(denominateur.getNb()==1))
        {
            Entier* e = new Entier(numerateur.getNb());
            return *e;
        }
        return *this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d = getNb() * d;
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
            compEnt->operator *(*this);
            comp->setReal(*this);
        }
        if (compRat) //La partie réelle du complexe est un rationnel
        {
            this->operator*(*compRat); //modifie la valeur de this
            comp->setReal(*this);
        }
        if (compReal) //La partie réelle du complexe est un réel
        {
            this->operator*(*compReal); //modifie la valeur de compReal
            comp->setReal(*compReal);
        }
        return *comp;
    }
}

Litterale& Rationnel::operator/(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        if (ent->getNb()==0)
            throw "Erreur : division par zero";
        setDenom(getDenom()*ent->getNb());
        simplification();
        //Test si ça donne un entier
        if ( (denominateur.getNb()==1) || (numerateur.getNb()==0) )
        {
            Entier* e = new Entier(numerateur.getNb());
            return *e;
        }
        else
        {
            return *this;
        }
    }
    if (rat) //c'est un rationnel
    {
        setNum(getNum()*rat->getDenom());
        setDenom(getDenom()*rat->getNum());
        simplification();
        //Test si ça donne un entier
        if ( (denominateur.getNb()==1) || (numerateur.getNb()==0) )
        {
            Entier* e = new Entier(numerateur.getNb());
            return *e;
        }
        else
        {
            return *this;
        }
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        double res = getNb() / d;
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
            if (compEnt->getNb()==0)
                throw "Erreur : division par zero";
            setDenom(getDenom()*compEnt->getNb());
            simplification();
            //Test si ça donne un entier
            if ( (denominateur.getNb()==1) || (numerateur.getNb()==0) )
            {
                Entier* e = new Entier(numerateur.getNb());
                return *e;
            }
            else
            {
                return *this;
            }
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

















