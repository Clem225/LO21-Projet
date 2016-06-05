#include "operateurs.h"

// Operateur d'affectation
Entier* Entier::operator=(Entier a)
{
    // On verifie que ce n'est pas un cas a=a;
    if(this!=&a)
    {
        nb=a.getNb();
    }

    return this;
}

// Operateur de comparaison
bool operator==(const Entier& a, const Entier& b)
{
    return a.getNb()==b.getNb();
}



Litterale* Entier::operator+(Litterale& e) {
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp))
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        nb+=ent->getNb();
        return this;
    }
    if (rat) //c'est un rationnel
    {
        rat->setNum(rat->getNum() + nb*rat->getDenom());
        rat->simplification();
        return rat;
    }
    if (real) //c'est un reel
    {
        real->setEntiere(real->getEntiere() + nb);
        return real;
    }
    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(this->operator +(*comp->getReal()))));
        return comp;
    }
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}



Litterale* Entier::operator-(Litterale& e)
{
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        nb-=ent->getNb();
        return this;
    }
    if (rat) //c'est un rationnel
    {
        rat->setNum(nb*rat->getDenom() - rat->getNum());
        rat->simplification();
        return rat;
    }
    if (real) //c'est un reel
    {
        double d= real->getNb();
        double nb2=nb;
        double result = nb2-d;
        real->setNb(result);
        return real;
    }
    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(this->operator -(*comp->getReal())   )));
        return comp;
    }
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}



Litterale* Entier::operator*(Litterale& e) {
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        nb*=ent->getNb();
        return this;
    }
    if (rat) //c'est un rationnel
    {
        rat->setNum(nb*rat->getNum());
        rat->simplification();
        //Test si ça donne un entier
        if ( (rat->getDenom()==1) || (rat->getNum()==0) )
        {
            Entier* e = new Entier(rat->getNum());
            return e;
        }
        return rat;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d = nb * d;
        real->setNb(d);
        return  real;
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



Litterale* Entier::operator/(Litterale& e) {
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
            return this;
        }
        else
        {
            Rationnel* r = new Rationnel(nb,ent->getNb());
            return r;
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
        return real;
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

    return NULL;
}
