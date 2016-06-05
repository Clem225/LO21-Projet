#include "operateurs.h"



Litterale* Reel::operator+(Litterale& e){
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
        return this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        nb+=d;
        if (getMantisse()==0)
            return new Entier(getNb());
        return this;
    }
    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   this->operator +(*comp->getReal())   )));
        return comp;
    }
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}



Litterale* Reel::operator-(Litterale& e){
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
        return this;
    }
    if (rat) //c'est un rationnel
    {
        rat->operator -(*this);
        this->setNb(-1*this->getNb()); //On échange le signe car opération dans le mauvais sens
        return this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d= nb-d;
        setNb(d);
        return this;
    }
    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   this->operator -(*comp->getReal())   )));
        return comp;
    }
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}



Litterale* Reel::operator*(Litterale& e){
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
        return this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d = nb * d;
        setNb(d);
        return this;
    }
    if (comp) //c'est un complexe
    {
        double a = this->getNb();
        double b = 0;
        double ap = comp->getReal()->getNb();
        double bp = comp->getImag()->getNb();
        double partReel = (a*ap)-(b*bp);
        std::ostringstream strs;
        strs << partReel;
        std::string partReelString = strs.str();

        double partImag = (a*bp)+(b*ap);
        std::ostringstream strs2;
        strs2 << partImag;
        std::string partImagString = strs2.str();

        LitteraleNumerique* partReelLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partReelString));
        LitteraleNumerique* partImagLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partImagString));

        comp->setReal(*partReelLit);
        comp->setImag(*partImagLit);



        return comp;
    }
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}



Litterale* Reel::operator/(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        double d = ent->getNb();
        d = getNb() /d;
        setNb(d);
        return this;
    }
    if (rat) //c'est un rationnel
    {
        double d = rat->getNb();
        d = getNb() / d;
        setNb(d);
        return this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d = getNb() / d;
        setNb(d);
        return this;
    }

    if (comp) //c'est un complexe
    {
        double a = this->getNb();
        double b = 0;
        double ap = comp->getReal()->getNb();
        double bp = comp->getImag()->getNb();

        double partReel = ((a*ap)+(b*bp))/(ap*ap+bp*bp);
        std::ostringstream strs;
        strs << partReel;
        std::string partReelString = strs.str();

        double partImag = (b*ap-a*bp)/(ap*ap+bp*bp);
        std::ostringstream strs2;
        strs2 << partImag;
        std::string partImagString = strs2.str();

        LitteraleNumerique* partReelLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partReelString));
        LitteraleNumerique* partImagLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partImagString));

        comp->setReal(*partReelLit);
        comp->setImag(*partImagLit);



        return comp;
    }
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}





