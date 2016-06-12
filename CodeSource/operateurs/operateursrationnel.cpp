#include "operateurs.h"
#include "../manager/controleur.h"

/*!
 * \file operateursrationnel.cpp
 * \brief Implementation des operateurs
 * \author Blanquet - Martinache
 * \version 0.1
 */
/*! \brief Operateur entre littérale */
Litterale* Rationnel::operator+(Litterale& e){
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
            return e;
        }
        return this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d+=this->getNb();
        real->setNb(d);
        return real;
    }

    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   this->operator +(*comp->getReal())   )));
        return comp;
    }
    if (exp) //c'est une expression
    {
        return exp->operator +(*this);
    }

    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return NULL;
}


/*! \brief Operateur entre littérale */
Litterale* Rationnel::operator-(Litterale& e){
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
        numerateur.setValue(-1*numerateur.getNb()); //On échange le signe car opération dans le mauvais sens
        return this;
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
            return e;
        }
        return this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d=this->getNb()-d;
        real->setNb(d);
        return real;
    }
    if (comp) //c'est un complexe
    {
        comp->setReal(dynamic_cast<LitteraleNumerique&>(*(   this->operator -(*comp->getReal())  )));
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
Litterale* Rationnel::operator*(Litterale& e){
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
        numerateur.setValue(getNum()*rat->getNum());
        denominateur.setValue(getDenom()*rat->getDenom());
        simplification();
        //Test si entier
        if ((numerateur.getNb()==0)||(denominateur.getNb()==1))
        {
            Entier* e = new Entier(numerateur.getNb());
            return e;
        }
        return this;
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        d = getNb() * d;
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
Litterale* Rationnel::operator/(Litterale& e){
    Entier* ent=dynamic_cast<Entier*>(&e);
    Rationnel* rat=dynamic_cast<Rationnel*>(&e);
    Reel* real=dynamic_cast<Reel*>(&e);
    Complexe* comp=dynamic_cast<Complexe*>(&e);
    Expression* exp = dynamic_cast<Expression*>(&e);
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
            return e;
        }
        else
        {
            return this;
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
            return e;
        }
        else
        {
            return this;
        }
    }
    if (real) //c'est un reel
    {
        double d = real->getNb();
        double res = getNb() / d;
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

















