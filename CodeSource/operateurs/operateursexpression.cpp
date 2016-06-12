#include "operateurs.h"
#include "../manager/controleur.h"


Litterale* Expression::operator+(Litterale& litt)
{
    //On teste le type de l'argument
    Expression* e1 = dynamic_cast<Expression*>(&litt);
    LitteraleNumerique* littNum1 = dynamic_cast<LitteraleNumerique*>(&litt);
    Complexe* c1 = dynamic_cast<Complexe*>(&litt);

    if (e1) //C'est une expression
    {
        std::string temp1 = this->toString();
        temp1=temp1.substr(1,temp1.length()-2);
        std::string temp2 = e1->toString();
        temp2=temp2.substr(1,temp2.length()-2);
        std::string temp3 = "'(" + temp1 + ")+(" + temp2 + ")'";
        Expression* newexp = new Expression(temp3);
        return newexp;
    }
    if (littNum1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + littNum1->toString() + " + ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }
    if (c1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + c1->toString() + " + ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }

    return NULL;
}

Litterale* Expression::operator-(Litterale& litt)
{
    //On teste le type de l'argument
    Expression* e1 = dynamic_cast<Expression*>(&litt);
    LitteraleNumerique* littNum1 = dynamic_cast<LitteraleNumerique*>(&litt);
    Complexe* c1 = dynamic_cast<Complexe*>(&litt);

    if (e1) //C'est une expression
    {
        std::string temp1 = this->toString();
        temp1=temp1.substr(1,temp1.length()-2);
        std::string temp2 = e1->toString();
        temp2=temp2.substr(1,temp2.length()-2);
        std::string temp3 = "'(" + temp1 + ")-(" + temp2 + ")'";
        Expression* newexp = new Expression(temp3);
        return newexp;
    }
    if (littNum1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + littNum1->toString() + " - ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }
    if (c1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + c1->toString() + " - ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }

    return NULL;
}

Litterale* Expression::operator*(Litterale& litt)
{
    //On teste le type de l'argument
    Expression* e1 = dynamic_cast<Expression*>(&litt);
    LitteraleNumerique* littNum1 = dynamic_cast<LitteraleNumerique*>(&litt);
    Complexe* c1 = dynamic_cast<Complexe*>(&litt);

    if (e1) //C'est une expression
    {
        std::string temp1 = this->toString();
        temp1=temp1.substr(1,temp1.length()-2);
        std::string temp2 = e1->toString();
        temp2=temp2.substr(1,temp2.length()-2);
        std::string temp3 = "'(" + temp1 + ")*(" + temp2 + ")'";
        Expression* newexp = new Expression(temp3);
        return newexp;
    }
    if (littNum1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + littNum1->toString() + " * ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }
    if (c1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + c1->toString() + " * ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }

    return NULL;
}

Litterale* Expression::operator/(Litterale& litt)
{
    //On teste le type de l'argument
    Expression* e1 = dynamic_cast<Expression*>(&litt);
    LitteraleNumerique* littNum1 = dynamic_cast<LitteraleNumerique*>(&litt);
    Complexe* c1 = dynamic_cast<Complexe*>(&litt);

    if (e1) //C'est une expression
    {
        std::string temp1 = this->toString();
        temp1=temp1.substr(1,temp1.length()-2);
        std::string temp2 = e1->toString();
        temp2=temp2.substr(1,temp2.length()-2);
        std::string temp3 = "'(" + temp1 + ")/(" + temp2 + ")'";
        Expression* newexp = new Expression(temp3);
        return newexp;
    }
    if (littNum1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + littNum1->toString() + " / ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }
    if (c1)
    {
        std::string temp = EVAL(this);
        temp+= "  " + c1->toString() + " / ";
        Controleur::getInstance().commande(temp);
        return NULL;
    }

    return NULL;
}

Litterale* Expression::NEG()
{
    std::string temp = this->toString();
    temp= temp.substr(1,temp.length()-2);
    std::string result = "'NEG(" + temp + ")'";
    Controleur::getInstance().commande(result);
    return NULL;
}

double Expression::getNb() const
{
    // Si aucun if n'est respecte (Normalement, ne peux pas arriver) -> Evite un warning
    return 0;
}

