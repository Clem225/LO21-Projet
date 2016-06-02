#include "operateurs.h"


Complexe* Complexe::NEG()
{
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}

Litterale* Complexe::operator+(Litterale& e)
{
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
        return rat->operator +(*this);
    }
    if (real) //c'est un reel
    {
        return real->operator +(*this);
    }
    if (comp) //c'est un complexe
    {
        Complexe * ctemp = new Complexe(getReal(),getImag());
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(this->getReal()->operator +(*comp->getReal()))));
        comp->setImag(dynamic_cast<LitteraleNumerique&>(*(ctemp->getImag()->operator +(*comp->getImag()))));
        return this;
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}




Litterale* Complexe::operator-(Litterale& e)
{
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
    if(comp)
    {
    Complexe * ctemp = new Complexe(getReal(),getImag());
    comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   this->getReal()->operator -(*comp->getReal())  )));
    comp->setImag(dynamic_cast<LitteraleNumerique&>(*(   ctemp->getImag()->operator -(*comp->getImag())  )));
    return comp;
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}




Litterale* Complexe::operator*(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        ent->operator*(*this);
    }
    if (rat) //c'est un rationnel
    {
        rat->operator *(*this);
    }
    if (real) //c'est un reel
    {
       real->operator *(*this);
    }
    if(comp)
    {
    Complexe * ctemp1 = new Complexe(getReal(),getImag());
    Complexe * ctemp2 = new Complexe(comp->getReal(),comp->getImag());

    comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   this->getReal()->operator*(*comp->getReal())  )));
    comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   comp->getReal()->operator-(  *(this->getImag()->operator *(*comp->getImag()))  )  )));

    comp->setImag(dynamic_cast<LitteraleNumerique&>(*(   ctemp1->getReal()->operator *(*ctemp2->getImag())  )));
    // A REFAIRE
    //comp->setImag(dynamic_cast<LitteraleNumerique&>(*(   comp->getImag()->operator +(  *(ctemp->getImag()->operator *(*comp->getReal()))  )  )));

    return comp;
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}



Litterale* Complexe::operator/(Litterale& e){

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}
