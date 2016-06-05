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
        /*
    Litterale* a = this->getReal();
    Litterale* b = this->getImag();
    Litterale* ap = comp->getReal();
    Litterale* bp = comp->getImag();

    // a * a' - b * b'
    LitteraleNumerique* partReel = (*a)*(*ap) + (*b)*(*bp);

    // a * b' + b * a'
    LitteraleNumerique* partImg = dynamic_cast<LitteraleNumerique*>(((this->getReal())->operator *(comp->getImag())));
    partImg->operator +(comp->getReal()->operator *(this->getReal()));

    Litterale* result = new Litterale(partReel,partImg);

    return result;
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;*/
    }
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
        Litterale* aSave = comp->getReal()->clone();
        Litterale* bSave = comp->getImag()->clone();

        Litterale* apSave = comp->getReal()->clone();
        Litterale* bpSave = comp->getImag()->clone();

        // On calcule a * a'
        LitteraleNumerique* partReel1 = dynamic_cast<LitteraleNumerique*>(aSave->operator *(*apSave));
        // On calcule b * b'
        LitteraleNumerique* partReel2 = dynamic_cast<LitteraleNumerique*>(bSave->operator *(*bpSave));
        // On calcule aa' - bb'
        LitteraleNumerique* partReel = dynamic_cast<LitteraleNumerique*>(partReel1->operator -(*partReel2));

        Litterale* aSave2 = comp->getReal()->clone();
        Litterale* bSave2 = comp->getImag()->clone();

        Litterale* apSave2 = comp->getReal()->clone();
        Litterale* bpSave2 = comp->getImag()->clone();

        // On calcule a * b'
        LitteraleNumerique* partImag1 = dynamic_cast<LitteraleNumerique*>(aSave2->operator *(*bpSave2));
        // On calcule b * a''
        LitteraleNumerique* partImag2 = dynamic_cast<LitteraleNumerique*>(bSave2->operator *(*apSave2));
        // On calcule ab' + ba'
        LitteraleNumerique* partImag = dynamic_cast<LitteraleNumerique*>(partImag1->operator +(*partImag2));

        comp->setReal(*partReel);
        comp->setImag(*partImag);


        delete aSave;
        delete bSave;

        delete aSave2;
        delete aSave2;

        delete apSave;
        delete bpSave;

        delete apSave2;
        delete bpSave2;


        return this;

    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}



Litterale* Complexe::operator/(Litterale& e){

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}
