#include "operateurs.h"
#include "../manager/controleur.h"

/*!
 * \file operateurscomplexes.cpp
 * \brief Implementation des operateurs
 * \author Blanquet - Martinache
 * \version 0.1
 */
/*! \brief Operateur entre littérale */
Complexe* Complexe::NEG()
{
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}
/*! \brief Operateur entre littérale */
Litterale* Complexe::operator+(Litterale& e)
{
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    Expression* exp = dynamic_cast<Expression*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp)&&!exp)
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
    if (exp) //c'est une expression
    {
        return exp->operator +(*this);
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}



/*! \brief Operateur entre littérale */
Litterale* Complexe::operator-(Litterale& e)
{
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    Expression* exp = dynamic_cast<Expression*>(&e);

    if ((!ent)&&(!rat)&&(!real)&&(!comp)&&!exp)
        throw "Erreur : operation impossible : l'un des operateurs n'est pas une litterale";

    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        ent->operator -(*this);
        this->getReal()->NEG();
        return this;
    }
    if (rat) //c'est un rationnel
    {
        rat->operator -(*this);
        this->getReal()->NEG();
        return this;
    }
    if (real) //c'est un reel
    {
        real->operator -(*this);
        this->getReal()->NEG();
        return this;
    }
    if(comp)
    {
        Complexe * ctemp = new Complexe(getReal(),getImag());
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   this->getReal()->operator -(*comp->getReal())  )));
        comp->setImag(dynamic_cast<LitteraleNumerique&>(*(   ctemp->getImag()->operator -(*comp->getImag())  )));
        return comp;
    }
    if (exp) //c'est une expression
    {
        std::string temp= this->toString() + "  ";
        temp += EVAL(exp) + " -";
        Controleur::getInstance().commande(temp);
        return NULL;
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}



/*! \brief Operateur entre littérale */
Litterale* Complexe::operator*(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    Expression* exp = dynamic_cast<Expression*>(&e);
    if (ent) //si le cast a réussi, c'est à dire si e est bien un entier
    {
        return ent->operator*(*this);
    }
    if (rat) //c'est un rationnel
    {
        return rat->operator *(*this);
    }
    if (real) //c'est un reel
    {
       return real->operator *(*this);
    }
    if(comp)
    {

        double a = this->getReal()->getNb();
        double b = this->getImag()->getNb();
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
    if (exp) //c'est une expression
    {
        std::string temp= this->toString() + "  ";
        temp += EVAL(exp) + " *";
        Controleur::getInstance().commande(temp);
        return NULL;
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}


/*! \brief Operateur entre littérale */
Litterale* Complexe::operator/(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    Expression* exp = dynamic_cast<Expression*>(&e);

    double a = this->getReal()->getNb();
    double b = this->getImag()->getNb();

    // Si c'est un entier
    if(ent)
    {

        double partReel = a/(ent->getNb());
        std::ostringstream strs;
        strs << partReel;
        std::string partReelString = strs.str();

        double partImag = b/(ent->getNb());
        std::ostringstream strs2;
        strs2 << partImag;
        std::string partImagString = strs2.str();

        LitteraleNumerique* partReelLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partReelString));
        LitteraleNumerique* partImagLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partImagString));

        this->setReal(*partReelLit);
        this->setImag(*partImagLit);

        return this;
    }
    if(rat)
    {
        double partReel = a/(rat->getNb());
        std::ostringstream strs;
        strs << partReel;
        std::string partReelString = strs.str();

        double partImag = b/(rat->getNb());
        std::ostringstream strs2;
        strs2 << partImag;
        std::string partImagString = strs2.str();

        LitteraleNumerique* partReelLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partReelString));
        LitteraleNumerique* partImagLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partImagString));

        this->setReal(*partReelLit);
        this->setImag(*partImagLit);

        return this;
    }
    if(real)
    {
        double partReel = a/(real->getNb());
        std::ostringstream strs;
        strs << partReel;
        std::string partReelString = strs.str();

        double partImag = b/(real->getNb());
        std::ostringstream strs2;
        strs2 << partImag;
        std::string partImagString = strs2.str();

        LitteraleNumerique* partReelLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partReelString));
        LitteraleNumerique* partImagLit = dynamic_cast<LitteraleNumerique*>(FactoryLitterale::getInstance().create(partImagString));

        this->setReal(*partReelLit);
        this->setImag(*partImagLit);

        return this;
    }
    // Division entre deux complexes
    if(comp)
    {

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
    if (exp) //c'est une expression
    {
        std::string temp= this->toString() + "  ";
        temp += EVAL(exp) + " /";
        Controleur::getInstance().commande(temp);
        return NULL;
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;

}
