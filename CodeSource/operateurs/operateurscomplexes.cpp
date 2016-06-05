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



        return comp;

    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}



Litterale* Complexe::operator/(Litterale& e){

    Complexe* comp=dynamic_cast<Complexe*>(&e);

    // Division entre deux complexes
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
        LitteraleNumerique* partReelNum = dynamic_cast<LitteraleNumerique*>(partReel1->operator +(*partReel2));
        // On calcule a'²
        Litterale* apSaveb = comp->getReal()->clone();
        LitteraleNumerique* partReel3 = dynamic_cast<LitteraleNumerique*>(apSaveb->operator *(*apSaveb));
        // On calcule b'²
        Litterale* bpSaveb = comp->getReal()->clone();
        LitteraleNumerique* partReel4 = dynamic_cast<LitteraleNumerique*>(bpSaveb->operator *(*bpSaveb));
        // On calcule a'² + b'²
        LitteraleNumerique* partReelDenom = dynamic_cast<LitteraleNumerique*>(partReel3->operator +(*partReel4));
        // On calcule la partie reel
        LitteraleNumerique* partReel = dynamic_cast<LitteraleNumerique*>(partReelNum->operator /(*partReelDenom));


        Litterale* aSave2 = comp->getReal()->clone();
        Litterale* bSave2 = comp->getImag()->clone();

        Litterale* apSave2 = comp->getReal()->clone();
        Litterale* bpSave2 = comp->getImag()->clone();

        // On calcule b * a'
        LitteraleNumerique* partImag1 = dynamic_cast<LitteraleNumerique*>(bSave2->operator *(*apSave2));
        // On calcule a * b'
        LitteraleNumerique* partImag2 = dynamic_cast<LitteraleNumerique*>(aSave2->operator *(*bpSave2));
        // On calcule ba' - ab'
        LitteraleNumerique* partImagNum = dynamic_cast<LitteraleNumerique*>(partImag1->operator -(*partImag2));
        // On calcule a'²
        Litterale* apSaveb2 = comp->getReal()->clone();
        LitteraleNumerique* partImag3 = dynamic_cast<LitteraleNumerique*>(apSaveb2->operator *(*apSaveb2));
        // On calcule b'²
        Litterale* bpSaveb2 = comp->getReal()->clone();
        LitteraleNumerique* partImag4 = dynamic_cast<LitteraleNumerique*>(bpSaveb2->operator *(*bpSaveb2));
        // On calcule a'² + b'²
        LitteraleNumerique* partImagDenom = dynamic_cast<LitteraleNumerique*>(partImag3->operator +(*partImag4));
        // On calcule la partie reel
        LitteraleNumerique* partImag = dynamic_cast<LitteraleNumerique*>(partImagNum->operator /(*partImagDenom));

        comp->setReal(*partReel);
        comp->setImag(*partImag);



        return comp;

    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}
