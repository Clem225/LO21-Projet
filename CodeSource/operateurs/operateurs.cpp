#include "operateurs.h"
#include <sstream>
#include <iostream>
#include <stack>


// Liste des opérateurs reconnus

bool estUnOperateurBinaire(const std::string& c)
{
    bool listOperateurBinaire =
            c=="+" ||
            c=="-" ||
            c=="*" ||
            c=="/" ||
            c=="DIV" ||
            c=="MOD" ||
            c=="STO" ||
            c=="$" ||
            c=="="  ||
            c=="!=" ||
            c=="<=" ||
            c==">=" ||
            c=="<" ||
            c==">" ||
            c=="AND" ||
            c=="OR";

    if(listOperateurBinaire)
        return true;

    return false;
}
bool estUnOperateurUnaire(const std::string& c)
{
    bool listOperateurUnaire =
            c=="NEG" ||
            c=="NUM" ||
            c=="DEN" ||
            c=="RE"  ||
            c=="IM"  ||
            c=="NOT" ||
            c=="EVAL";

    if(listOperateurUnaire)
        return true;

    return false;
}

bool estOperateur(const std::string& str)
{
    bool listOperateur =
            estUnOperateurBinaire(str) ||
            estUnOperateurUnaire(str);


    if(listOperateur)
        return true;

        return false;

}


/*Opérateurs additionnels*/

Entier* DIV(Entier* e1, Entier* e2) {
        return e1->setValue(e1->getNb()/e2->getNb());
}

Entier* MOD(Entier* e1, Entier* e2) {
        return e1->setValue(static_cast<int>(e1->getNb())%(static_cast<int>(e2->getNb())));
}

std::string EVAL(Expression& expr) {
    std::string exp = expr.getExpr();
    exp.erase(0,1);
    exp.erase(exp.length(),1);
    std::stack<std::string> pileOp;
    std::string expim1;
    std::string expi;
     for(unsigned int i=0;i<exp.size();i++)
     {
         expi = "";
         expim1= "";
         expi += exp[i];
         expim1 += exp[i-1];
        if (estOperateur(expi))
        {
            //On teste si c'est pas un '-' non opérateur
            if (!estOperateur(expim1) && expim1!="(" )
                pileOp.push(expi); //On l'empile
        }
        else
        {
            if (expi=="(" )
            {
                int j = i;
                while (exp[j]!=')' )
                    j++;
                std:: string temp = exp;
                temp.substr(i+1,j); //Prend l'exp entre parenthèses
                Expression* newexpr = new Expression(temp);
                std:: string res = EVAL(*newexpr);
                exp.replace(i,j+1-i,res); //On remplace cette partie entre parenthèses par son évaluation
            }
        }
    }

    //On enleve les operateurs du string
    for (unsigned int i=0;i<exp.size();i++)
    {
        expi = "";
        expim1= "";
        expi += exp[i];
        expim1 += exp[i-1];
        if (estOperateur(expi))
        {
            //On teste si c'est pas un '-' non opérateur
            if (!estOperateur(expim1) && expim1!="(")
                exp[i]=' '; //On remplace les op. par un espace
        }
    }

    //Ici, on obtient un string sans opérateur
    //On met les opérateurs à la fin du string en les dépilant
    while (!pileOp.empty())
    {
        exp = exp + " " + pileOp.top();
        pileOp.pop();
    }
    return exp;
}

