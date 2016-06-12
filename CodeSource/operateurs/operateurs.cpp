#include "operateurs.h"


/*!
 * \file operateurs.cpp
 * \brief Implementation des operateurs
 * \author Blanquet - Martinache
 * \version 0.1
 */

// Liste des opérateurs reconnus
/*! \brief Verifie si str est un opérateur binaire */
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
            c=="OR" ||
            c=="IFT";

    if(listOperateurBinaire)
        return true;

    return false;
}
/*! \brief Verifie si str est un opérateur unaire */
bool estUnOperateurUnaire(const std::string& c)
{
    bool listOperateurUnaire =
            c=="NEG" ||
            c=="NUM" ||
            c=="DEN" ||
            c=="RE"  ||
            c=="IM"  ||
            c=="NOT" ||
            c=="EVAL" ||
            c=="FORGET";

    if(listOperateurUnaire)
        return true;

    return false;
}
/*! \brief Verifie si str est un opérateur zero */
bool estUnOperateurZero(const std::string& c)
{

    bool listOperateurZero =
            c=="EDIT" ||
            c=="DUP" ||
            c=="DROP" ||
            c=="SWAP" ||
            c=="LASTOP" ||
            c=="LASTARGS" ||
            c=="UNDO" ||
            c=="REDO" ||
            c=="CLEAR";

    if(listOperateurZero)
        return true;

    return false;
}
/*! \brief Verifie si str est un opérateur */
bool estOperateur(const std::string& str)
{
    bool listOperateur =
            estUnOperateurBinaire(str) ||
            estUnOperateurUnaire(str) ||
            estUnOperateurZero(str);


    if(listOperateur)
        return true;

    return false;

}


/*Opérateurs additionnels*/
/*! \brief La fonction DIV effectue la division entiere entre deux entiers */
Entier* DIV(Entier* e1, Entier* e2) {
        return e1->setValue(e1->getNb()/e2->getNb());
}
/*! \brief La fonction MOD renvoie le reste de la division entre deux entiers */
Entier* MOD(Entier* e1, Entier* e2) {
        return e1->setValue(static_cast<int>(e1->getNb())%(static_cast<int>(e2->getNb())));
}
/*! \brief Evalue une litterale */
std::string EVAL(Litterale* litt) {
    Expression* expr = dynamic_cast<Expression*>(litt);
    Programme* progr = dynamic_cast<Programme*>(litt);

    if (expr) //C'est une expression
    {
        std::string exp = expr->toString();
        std::string finalResult="";
        exp.erase(0,1);
        exp.erase(exp.length(),1);
        std::string expi;
        bool isNEG=false;
        bool prioActiv=false;
        std::string prioTemp="";
        int compteurParenthese;
         for(unsigned int i=0;i<exp.size()-1;i++)
         {
            prioActiv=false;
            isNEG=false;
            expi = "";
            expi += exp[i];
            if (estOperateur(expi)&&i!=0) //Si c'est un opérateur
            {

                if (exp[i+1]=='-') //ça veut dire que c'est un moins non opérateur, un "NEG" si on peut dire
                {
                    isNEG=true; //On le retient
                    exp.erase(i+1,i);
                }

                if (expi=="*"||expi=="/") //Si c'est un * ou /, on supprime l'operateur precedent pour le mettre à la fin ensuite (pour respecter les priorités)
                {
                    prioTemp="";
                    prioTemp+=finalResult[finalResult.length()-1];
                    if (estOperateur(prioTemp))
                    {
                        prioActiv=true;
                        finalResult.erase(finalResult.length()-1,1);
                    }
                }

                int tailleParenthese;
                if (exp[i+1]=='(') //Si le caractère suivant est une parenthèse
                {
                    //On cherche la parenthèse fermante, en prenant en compte les parenthèses imbriquées
                    int j = i+2;
                    compteurParenthese=0;
                    while ( (exp[j]!=')') || (compteurParenthese!=0) )
                    {
                        if (exp[j]=='(')
                            compteurParenthese++;
                        if (exp[j]==')')
                            compteurParenthese--;
                        j++;
                    }
                    std:: string temp = exp.substr(i+2,j-(i+2)); //Prend l'exp entre parenthèses
                    temp= "'"+temp+"'"; //On rajoute les quotes
                    Expression* newexpr = new Expression(temp); //On crée une expression comportant uniquement la paranthèse
                    std::string res = EVAL(newexpr); //On évalue la parenthèse
                    tailleParenthese=j-i;
                    finalResult+=res;
                    i+=tailleParenthese;
                }
                else
                {
                    bool testOperator=false;
                    //On teste si ça peut être un operateur type STO,NEG,DIV...
                    if (exp[i+1]<='Z'&&exp[i+1]>='A') //c'est une lettre majuscule donc potentiellement un operateur unaire/binaire
                    {
                        std::string testOp = exp.substr(i+1,2); //On regarde si c'est un op à deux lettres
                        if (estUnOperateurUnaire(testOp)) //C'est un operateur unaire à deux lettres (RE ou IM)
                        {
                            testOperator=true;
                            int j=i+3; //On place j sur la premiere parenthese
                            while (exp[j]!=')')
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            std::string temp = exp.substr(i+4,j-(i+4));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp=EVAL(tempexp);
                            finalResult+=" "+argOp;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                        if (estUnOperateurBinaire(testOp)) //C'est un operateur binaire à deux lettres (OR)
                        {
                            testOperator=true;
                            int j=i+3; //On place j sur la premiere parenthese
                            while (exp[j]!=',') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la virgule, on save la position de la virgule
                            int posVirgule=j;
                            std::string temp = exp.substr(i+4,j-(i+4));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp1=EVAL(tempexp);
                            while (exp[j]!=')') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            temp = exp.substr(posVirgule+1,j-(posVirgule+1));
                            temp="'"+temp+"'";
                            Expression* tempexp2= new Expression(temp);
                            std::string argOp2=EVAL(tempexp2);
                            finalResult+=" "+argOp1;
                            finalResult+=" "+argOp2;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                        testOp=exp.substr(i+1,3); //On regarde si c'est un op à trois lettres
                        if (estUnOperateurUnaire(testOp)) //C'est un operateur unaire à trois lettres
                        {
                            testOperator=true;
                            int j=i+4; //On place j sur la premiere parenthese
                            while (exp[j]!=')')
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            std::string temp = exp.substr(i+5,j-(i+5));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp=EVAL(tempexp);
                            finalResult+=" "+argOp;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                        if (estUnOperateurBinaire(testOp)) //C'est un operateur binaire à trois lettres
                        {
                            testOperator=true;
                            int j=i+4; //On place j sur la premiere parenthese
                            while (exp[j]!=',') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la virgule, on save la position de la virgule
                            int posVirgule=j;
                            std::string temp = exp.substr(i+5,j-(i+5));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp1=EVAL(tempexp);
                            while (exp[j]!=')') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            temp = exp.substr(posVirgule+1,j-(posVirgule+1));
                            temp="'"+temp+"'";
                            Expression* tempexp2= new Expression(temp);
                            std::string argOp2=EVAL(tempexp2);
                            finalResult+=" "+argOp1;
                            finalResult+=" "+argOp2;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                    }
                    if (testOperator==false) //Le caractère suivant n'est ni une parenthèse ni un operateur unaire/binaire, c'est donc un nombre
                    {
                        int j=i;
                        while ( (exp[j+1]<='9'&&exp[j+1]>='0') || (exp[j+1]<='Z'&&exp[j+1]>='A') || (exp[j+1]=='.') || (exp[j+1]=='$') )
                            j++;
                        std::string temp=exp.substr(i+1,j-i);
                        finalResult+=" "+temp;
                        if (isNEG)
                        {
                            finalResult+=" ";
                            finalResult+="NEG";
                        }
                        i=j;
                    }
                }
                finalResult+=" "+expi;
                if (prioActiv) //C'est ici qu'on remet l'opérateur précédent à la fin en cas de '*' ou '/' pour respecter les priorités
                {
                    finalResult+=" "+prioTemp;
                }

            }
            else //Ce n'est pas un opérateur
            {
                //On teste si ça peut être un programme
                if (exp[i]=='[' || exp[i]==']')
                    return "error"; //On signale une erreur

                if (exp[i]=='(') //ça veut dire que l'expression commence par une parenthèse
                {
                    //On cherche la parenthèse fermante, en prenant en compte les parenthèses imbriquées
                    int j = i+1;
                    compteurParenthese=0;
                    while ( (exp[j]!=')') || (compteurParenthese!=0) )
                    {
                        if (exp[j]=='(')
                            compteurParenthese++;
                        if (exp[j]==')')
                            compteurParenthese--;
                        j++;
                    }
                    std:: string temp = exp.substr(i+1,j-(i+1)); //Prend l'exp entre parenthèses
                    temp= "'"+temp+"'"; //On rajoute les quotes
                    Expression* newexpr = new Expression(temp); //On crée une expression comportant uniquement la paranthèse
                    std::string res = EVAL(newexpr); //On évalue la parenthèse
                    int tailleParenthese=j-i;
                    finalResult+=res;
                    i+=tailleParenthese;
                }
                if (exp[i]=='-') //On regle le probleme si ça commence par un '-'
                {
                    i++;
                    int j=i;
                    while ( (exp[j]<='9'&&exp[j]>='0') || (exp[j]<='Z'&&exp[j]>='A') || (exp[j]=='.') || (exp[j]=='$') )
                        j++;
                    finalResult+=" "+exp.substr(i,j-i);
                    finalResult+=" NEG";
                    i=j-1;
                }
                else //traitement normal, ça ne commence pas par une parenthèse
                {
                    bool testOperator=false;
                    //On teste si ça peut être un operateur type STO,NEG,DIV...
                    if (exp[i]<='Z'&&exp[i]>='A') //c'est une lettre majuscule donc potentiellement un operateur unaire/binaire
                    {
                        std::string testOp = exp.substr(i,2); //On regarde si c'est un op à deux lettres
                        if (estUnOperateurUnaire(testOp)) //C'est un operateur unaire à deux lettres (RE ou IM)
                        {
                            testOperator=true;
                            int j=i+2; //On place j sur la premiere parenthese
                            while (exp[j]!=')')
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            std::string temp = exp.substr(i+3,j-(i+3));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp=EVAL(tempexp);
                            finalResult+=" "+argOp;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                        if (estUnOperateurBinaire(testOp)) //C'est un operateur binaire à deux lettres (OR)
                        {
                            testOperator=true;
                            int j=i+2; //On place j sur la premiere parenthese
                            while (exp[j]!=',') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la virgule, on save la position de la virgule
                            int posVirgule=j;
                            std::string temp = exp.substr(i+3,j-(i+3));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp1=EVAL(tempexp);
                            while (exp[j]!=')') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            temp = exp.substr(posVirgule+1,j-(posVirgule+1));
                            temp="'"+temp+"'";
                            Expression* tempexp2= new Expression(temp);
                            std::string argOp2=EVAL(tempexp2);
                            finalResult+=" "+argOp1;
                            finalResult+=" "+argOp2;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                        testOp=exp.substr(i,3); //On regarde si c'est un op à trois lettres
                        if (estUnOperateurUnaire(testOp)) //C'est un operateur unaire à trois lettres
                        {
                            testOperator=true;
                            int j=i+3; //On place j sur la premiere parenthese
                            while (exp[j]!=')')
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            std::string temp = exp.substr(i+4,j-(i+4));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp=EVAL(tempexp);
                            finalResult+=" "+argOp;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                        if (estUnOperateurBinaire(testOp)) //C'est un operateur binaire à trois lettres
                        {
                            testOperator=true;
                            int j=i+3; //On place j sur la premiere parenthese
                            while (exp[j]!=',') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la virgule, on save la position de la virgule
                            int posVirgule=j;
                            std::string temp = exp.substr(i+4,j-(i+4));
                            temp="'"+temp+"'";
                            Expression* tempexp= new Expression(temp);
                            std::string argOp1=EVAL(tempexp);
                            while (exp[j]!=')') //On cherche l premier operateur
                                j++;
                            //A ce stade j est sur la derniere parenthese
                            temp = exp.substr(posVirgule+1,j-(posVirgule+1));
                            temp="'"+temp+"'";
                            Expression* tempexp2= new Expression(temp);
                            std::string argOp2=EVAL(tempexp2);
                            finalResult+=" "+argOp1;
                            finalResult+=" "+argOp2;
                            finalResult+=" "+testOp;
                            i=j;
                        }
                    }
                    if (testOperator==false)
                    {
                        int j=i;
                        if (i+2<exp.length())
                        {
                            while ( (exp[j+1]<='9'&&exp[j+1]>='0') || (exp[j+1]<='Z'&&exp[j+1]>='A') || (exp[j+1]=='.') || (exp[j+1]=='$') )
                                j++;
                            finalResult+=" "+exp.substr(i,j+1-i);
                            i=j;
                        }
                        else
                        {
                            finalResult+=exp[i];
                        }
                    }
                }
            }

        }
        return finalResult;
    }

    else //C'est un programme
    {
        std::string prog=progr->toString();
        prog = prog.substr(1,prog.length()-2); //On enleve les crochets
        return prog;
    }
}

