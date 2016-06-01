#include "operateurs.h"


Litterale& Complexe::operator+(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp))
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        ent->operator +(*this);
    }
    if (rat) //c'est un rationnel
    {
        rat->operator +(*this);
    }
    if (real) //c'est un reel
    {
        real->operator +(*this);
    }
    if (comp) //c'est un complexe
    {
        // On cherche la partie reelle du 2e complexe
        Entier* compEnt=dynamic_cast<Entier*>(comp->getReal());
        Rationnel* compRat=dynamic_cast<Rationnel*>(comp->getReal());
        Reel* compReal=dynamic_cast<Reel*>(comp->getReal());

        if (compEnt)
        {
            this->operator +(*compEnt);
        }
        if (compRat)
        {
            this->operator +(*compRat);
        }
        if (compReal)
        {
            this->operator +(*compReal);
        }

        //On cherche le type de la partie imaginaire du premier complexe
        Entier* imag1Ent=dynamic_cast<Entier*>(getImag());
        Rationnel* imag1Rat=dynamic_cast<Rationnel*>(getImag());
        Reel* imag1Real=dynamic_cast<Reel*>(getImag());

        //On cherche le type de la partie imaginaire du 2e complexe
        Entier* imag2Ent=dynamic_cast<Entier*>(comp->getImag());
        Rationnel* imag2Rat=dynamic_cast<Rationnel*>(comp->getImag());
        Reel* imag2Real=dynamic_cast<Reel*>(comp->getImag());

        if (imag1Ent) //La partie imaginaire du 1er du complexe est un entier
        {

            if (imag2Ent) //Les deux parties imaginaires sont entieres
            {
                imag1Ent->operator +(*imag2Ent);
                this->setImag(*imag1Ent);
            }
            if (imag2Rat) //La partie im du 2e est rationnelle
            {
                imag1Ent->operator +(*imag2Rat);
                this->setImag(*imag2Rat);
            }
            if (imag2Real)
            {
                imag1Ent->operator +(*imag2Real);
                this->setImag(*imag2Real);
            }
        }

        if (imag1Rat) //La partie réelle du complexe est un rationnel
        {
            if (imag2Ent) //Les deux parties imaginaires sont entieres
            {
                imag1Rat->operator +(*imag2Ent);
                this->setImag(*imag1Rat);
            }
            if (imag2Rat) //La partie im du 2e est rationnelle
            {
                imag1Rat->operator +(*imag2Rat);
                imag1Rat->simplification();
                //Test si ça donne un entier
                if ( (imag1Rat->getDenom()==1) || (imag1Rat->getNum()==0) )
                {
                    Entier* e = new Entier(imag1Rat->getNum());
                    this->setImag(*e);
                }
                else
                {
                    this->setImag(*imag1Rat);
                }
            }
            if (imag2Real)
            {
                imag1Rat->operator +(*imag2Real);
                this->setImag(*imag2Real);
            }
        }
        if (imag1Real) //La partie im du 2e complexe est un réel
        {
            if (imag2Ent) //Les deux parties imaginaires sont entieres
            {
                imag1Real->operator +(*imag2Ent);
                this->setImag(*imag1Real);
            }
            if (imag2Rat) //La partie im du 2e est rationnelle
            {
                imag1Real->operator +(*imag2Rat);
                this->setImag(*imag1Real);
            }
            if (imag2Real)
            {
                imag1Real->operator +(*imag2Real);
                this->setImag(*imag1Real);
            }
        }
        return *this;
    }
}




Litterale& Complexe::operator-(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp))
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        ent->operator -(*this);
        this->getReal()->NEG();
    }
    if (rat) //c'est un rationnel
    {
        rat->operator -(*this);
        this->getReal()->NEG();
    }
    if (real) //c'est un reel
    {
        real->operator -(*this);
        this->getReal()->NEG();
    }
    if (comp) //c'est un complexe
    {
        // On cherche la partie reelle du 2e complexe
        Entier* compEnt=dynamic_cast<Entier*>(comp->getReal());
        Rationnel* compRat=dynamic_cast<Rationnel*>(comp->getReal());
        Reel* compReal=dynamic_cast<Reel*>(comp->getReal());

        if (compEnt)
        {
            this->operator -(*compEnt);
        }
        if (compRat)
        {
            this->operator -(*compRat);
        }
        if (compReal)
        {
            this->operator -(*compReal);
        }

        //On cherche le type de la partie imaginaire du premier complexe
        Entier* imag1Ent=dynamic_cast<Entier*>(getImag());
        Rationnel* imag1Rat=dynamic_cast<Rationnel*>(getImag());
        Reel* imag1Real=dynamic_cast<Reel*>(getImag());

        //On cherche le type de la partie imaginaire du 2e complexe
        Entier* imag2Ent=dynamic_cast<Entier*>(comp->getImag());
        Rationnel* imag2Rat=dynamic_cast<Rationnel*>(comp->getImag());
        Reel* imag2Real=dynamic_cast<Reel*>(comp->getImag());

        if (imag1Ent) //La partie imaginaire du 1er du complexe est un entier
        {

            if (imag2Ent) //Les deux parties imaginaires sont entieres
            {
                imag1Ent->operator -(*imag2Ent);
                this->setImag(*imag1Ent);
            }
            if (imag2Rat) //La partie im du 2e est rationnelle
            {
                imag1Ent->operator -(*imag2Rat);
                this->setImag(*imag2Rat);
            }
            if (imag2Real)
            {
                imag1Ent->operator -(*imag2Real);
                this->setImag(*imag2Real);
            }
        }

        if (imag1Rat) //La partie réelle du complexe est un rationnel
        {
            if (imag2Ent) //Les deux parties imaginaires sont entieres
            {
                imag1Rat->operator -(*imag2Ent);
                this->setImag(*imag1Rat);
            }
            if (imag2Rat) //La partie im du 2e est rationnelle
            {
                imag1Rat->operator -(*imag2Rat);
                imag1Rat->simplification();
                //Test si ça donne un entier
                if ( (imag1Rat->getDenom()==1) || (imag1Rat->getNum()==0) )
                {
                    Entier* e = new Entier(imag1Rat->getNum());
                    this->setImag(*e);
                }
                else
                {
                    this->setImag(*imag1Rat);
                }
            }
            if (imag2Real)
            {
                imag1Rat->operator -(*imag2Real);
                this->setImag(*imag2Real);
            }
        }
        if (imag1Real) //La partie im du 2e complexe est un réel
        {
            if (imag2Ent) //Les deux parties imaginaires sont entieres
            {
                imag1Real->operator -(*imag2Ent);
                this->setImag(*imag1Real);
            }
            if (imag2Rat) //La partie im du 2e est rationnelle
            {
                imag1Real->operator -(*imag2Rat);
                this->setImag(*imag1Real);
            }
            if (imag2Real)
            {
                imag1Real->operator -(*imag2Real);
                this->setImag(*imag1Real);
            }
        }
        return *this;
    }
}




/*Litterale& operator*(Litterale& e){

}




Litterale& operator/(Litterale& e){

}*/
