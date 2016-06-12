#include "controleur.h"

#include "../litterales/litterales.h"
#include "../operateurs/operateurs.h"

#include "../GUI/mainwindow.h"


#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <QDebug>

/*!
 * \file controleur.cpp
 * \brief Controleur avec Memento
 * \author Blanquet - Martinache
 * \version 0.1
 */


/*! \brief Sauvegarde l'état du controleur */
void Controleur::save()
{
    // Memento
    CareTaker& careTaker = CareTaker::getInstance();
    // Sauvegarde
    Controleur::getInstance().setState(Controleur::getInstance().getState());
    careTaker.add(Controleur::getInstance().saveStateToMemento());
    careTaker.current=careTaker.number();
}

/*! \brief Redo */
void Controleur::redo()
{
    // Memento
    CareTaker& careTaker = CareTaker::getInstance();

    careTaker.current++;
    if(careTaker.current>careTaker.number())
        careTaker.current=careTaker.number()-1;

    this->getStateFromMemento(careTaker.get(careTaker.current));
    MainWindow::getInstance()->refreshPile();

}

/*! \brief Undo */
void Controleur::undo()
{

    CareTaker& careTaker = CareTaker::getInstance();


    if(careTaker.number()==careTaker.current)
    {
            this->save();
            careTaker.current--;
    }


    careTaker.current--;

    if(careTaker.current<0)
        careTaker.current=0;

    // Memento
    this->getStateFromMemento(careTaker.get(careTaker.current));
    MainWindow::getInstance()->refreshPile();
}

/*! \brief Execute le contenu de la pile */
void Controleur::executer()
{



    // On recupere le haut de la pile
    Operande* topOperande = pile.top();
    Operateur* monOperateur = dynamic_cast<Operateur*>(topOperande);



   if(monOperateur->toString() != "UNDO" && monOperateur->toString() != "REDO")
    {
    this->save();
    }



            // On l'enleve de la pile
            pile.pop();
            // On verifie son arite

            Zero* operateurZero = dynamic_cast<Zero*>(monOperateur);
            Unaire* operateurUnaire = dynamic_cast<Unaire*>(monOperateur);
            Binaire* operateurBinaire = dynamic_cast<Binaire*>(monOperateur);
            if(operateurZero)
            {
                if(operateurZero->toString() == "EDIT")
                {
                    MainWindow::getInstance()->programmes();
                    return;
                }
                if(operateurZero->toString() == "DUP")
                {
                    // On recupere la premiere opérande
                    Operande* v1 = pile.top();
                    this->empiler(v1);
                }
                if(operateurZero->toString() == "DROP")
                {
                    pile.pop();
                }
                if(operateurZero->toString() == "CLEAR")
                {
                    while(!pile.empty())
                        pile.pop();
                }
                if(operateurZero->toString() == "SWAP")
                {
                    // On recupere la premiere opérande
                    Operande* v1 = pile.top();
                    pile.pop();
                    Operande* v2 = pile.top();
                    pile.pop();
                    this->empiler(v1);
                    this->empiler(v2);
                }
                if(operateurZero->toString() == "UNDO")
                {

                    this->undo();
                }
                if(operateurZero->toString() == "REDO")
                {
                    this->redo();

                }
                if(operateurZero->toString() == "LASTOP")
                {
                    this->empiler(FactoryOperateur::getInstance(), this->lastOP);
                    this->executer();

                }
                if(operateurZero->toString() == "LASTARGS")
                {
                    this->empiler(FactoryLitterale::getInstance(), this->lastArgs);

                }

            }
            if(operateurUnaire)
            {
                if(pile.size()>=1)
                {
                    // On recupere la premiere opérande
                    Operande* v1 = pile.top();

                    Litterale* l1 = dynamic_cast<Litterale*>(v1);
                    // Si ce n'est pas une littérale, c'est un autre opérateur, on relance donc execution
                    if(!l1)
                        this->executer();

                    // On enleve la littérale de la pile
                    pile.pop();

                    // On cree un pointeur vers le resultat
                    Litterale* res = 0;

                    if(operateurUnaire->toString() == "NEG")
                    {
                        res=l1->NEG();
                        if (res)
                            this->empiler(res);
                    }

                    if(operateurUnaire->toString() == "NUM")
                    {
                        Rationnel* r1 = dynamic_cast<Rationnel*>(l1);
                        Entier* e1 = dynamic_cast<Entier*>(l1);
                        if (r1||e1)
                        {
                            if (r1)
                                res= new Entier(r1->getNum());
                            if (e1)
                                res=e1;
                            this->empiler(res);;
                            MainWindow::getInstance()->setMsg("NUM bien effectué !");
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l1);
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp = exp1->toString();
                                temp=temp.substr(1,temp.length()-2);
                                std::string result = "'NUM("+temp+")'";
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                this->empiler(l1);
                                MainWindow::getInstance()->setMsg("Erreur : l'operateur NUM ne s'applique que sur des rationnels des entiers ou des expressions !");
                            }
                        }
                    }

                    if(operateurUnaire->toString() == "DEN")
                    {
                        Rationnel* r1 = dynamic_cast<Rationnel*>(l1);
                        Entier* e1 = dynamic_cast<Entier*>(l1);
                        if (r1||e1)
                        {
                            if (r1)
                                res= new Entier(r1->getDenom());
                            if (e1)
                                res= new Entier(1);
                            this->empiler(res);;
                            MainWindow::getInstance()->setMsg("DEN bien effectué !");
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l1);
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp = exp1->toString();
                                temp=temp.substr(1,temp.length()-2);
                                std::string result = "'DEN("+temp+")'";
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                this->empiler(l1);
                                MainWindow::getInstance()->setMsg("Erreur : l'operateur DEN ne s'applique que sur des rationnels ou des entiers !");
                            }
                        }
                    }
                    if(operateurUnaire->toString() == "RE")
                    {
                        Complexe* c1 = dynamic_cast<Complexe*>(l1);
                        LitteraleNumerique* littNum = dynamic_cast<LitteraleNumerique*>(l1);
                        if (c1||littNum)
                        {
                            if (c1)
                            {
                               res = c1->getReal();
                               this->empiler(res);;
                               MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                            if (littNum)
                            {
                                this->empiler(littNum);
                                MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l1);
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp = exp1->toString();
                                temp=temp.substr(1,temp.length()-2);
                                std::string result = "'RE("+temp+")'";
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                this->empiler(l1);
                                MainWindow::getInstance()->setMsg("Erreur : l'operateur RE ne s'applique que sur des complexes ou expressions contenant un complexe !");
                            }
                        }
                    }
                    if(operateurUnaire->toString() == "IM")
                    {
                        Complexe* c1 = dynamic_cast<Complexe*>(l1);
                        LitteraleNumerique* littNum = dynamic_cast<LitteraleNumerique*>(l1);
                        if (c1||littNum)
                        {
                            if (c1)
                            {
                               res = c1->getImag();
                               this->empiler(res);;
                               MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                            if (littNum)
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                                MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l1);
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp = exp1->toString();
                                temp=temp.substr(1,temp.length()-2);
                                std::string result = "'IM("+temp+")'";
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                this->empiler(l1);
                                MainWindow::getInstance()->setMsg("Erreur : l'operateur RE ne s'app");
                            }
                        }
                    }

                    if(operateurUnaire->toString() == "NOT")
                    {
                        Entier* ent=dynamic_cast<Entier*>(l1);
                        if (ent)
                        {
                            if (ent->getNb()==0)
                            {
                                res = new Entier(1);
                                this->empiler(res);;
                            }
                            else
                            {
                                res = new Entier(0);
                                this->empiler(res);;
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l1);
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp = exp1->toString();
                                temp=temp.substr(1,temp.length()-2);
                                std::string result = "'NOT("+temp+")'";
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                res = new Entier(0);
                                this->empiler(res);
                            }
                        }
                    }
                    if(operateurUnaire->toString() == "EVAL")
                    {
                        Expression* expr=dynamic_cast<Expression*>(l1);
                        Programme* progr=dynamic_cast<Programme*>(l1);
                        if (expr||progr)
                        {
                            std::string temp;
                            if (expr)
                                temp = EVAL(expr);
                            if (progr)
                                temp = EVAL(progr);
                            // Si find ne trouve pas, il renvoie npos (= -1)
                            if (temp.find("error")!=std::string::npos)
                            {
                                this->pile.push(l1);
                                MainWindow::getInstance()->setMsg("Erreur : un caractère non autorisé pour l'évaluation était dans l'expression/programme !");
                            }
                            else
                                this->commande(temp);
                        }
                        else
                        {
                            this->empiler(l1);
                            MainWindow::getInstance()->setMsg("Erreur : EVAL ne s'applque que sur des expressions ou des programmes !");
                        }
                    }
                    if(operateurUnaire->toString() == "FORGET")
                    {
                        Expression* expr=dynamic_cast<Expression*>(l1);
                        if (expr)
                        {
                            std::string temp = expr->toString();
                            //On enleve les quotes
                            temp=temp.substr(1,temp.length()-2);
                            //On cherche l'atome correspondant
                            Atome* corres=nullptr;
                            for (AtomeManager::Iterator it = AtomeManager::getInstance().getIterator(); !it.isDone();it.next())
                            {
                                if (it.current().getAtome()==temp) //On a trouvé l'atome dans atomMng
                                {
                                    corres=&it.current();
                                    break;
                                }
                            }
                            if (corres) //La variable existe bien
                            {
                                AtomeManager::getInstance().delAtome(corres);
                                MainWindow::getInstance()->setMsg("Variable supprimée !");
                            }
                            else
                            {
                                MainWindow::getInstance()->setMsg("Erreur : la variable n'existe pas !");
                                this->empiler(l1);
                            }
                        }
                        else
                        {
                            this->empiler(l1);
                            MainWindow::getInstance()->setMsg("Erreur : FORGET ne s'applque que sur des expressions (qui représentent des noms de variable !");
                        }
                    }

                }
                else
                {
                    // Si on arrive ici, c'est qu'il n'y a pas assez d'élément dans la pile
                    MainWindow::getInstance()->setMsg("Erreur : Pas assez d'élément !");
                }
            }
            if(operateurBinaire)
            {
                // Si c'est un opérateur binaire, il faut que la pile soit supérieur ou égale à 2
                if(pile.size()>=2)
                {
                // On recupere la premiere opérande
                Operande* v1 = pile.top();

                Litterale* l1 = dynamic_cast<Litterale*>(v1);
                // Si ce n'est pas une littérale, c'est un autre opérateur, on relance donc execution
                if(!l1)
                    this->executer();

                // On enleve la littérale de la pile
                pile.pop();

                // On recupere le deuxieme opérande
                Operande* v2 = pile.top();

                Litterale* l2 = dynamic_cast<Litterale*>(v2);
                // Si ce n'est pas une littérale, on relance executer
                if(!l2)
                    this->executer();

                // On enleve la littérale de la pile
                pile.pop();

                //On cree une serie de bool pour un test ulterieur
                bool isDiv=false;
                bool isMod=false;
                bool isSto=false;
                bool isComp=false;
                bool isEqual=false;
                bool isNotEqual=false;
                bool isInfOrEqual=false;
                bool isSupOrEqual=false;
                bool isInf=false;
                bool isSup=false;
                bool isAND=false;
                bool isOR=false;
                bool isIFT=false;
                // On cree un pointeur vers le resultat
                Litterale* res = 0;
                // On fait le calcul correspondant à l'opérateur (qui renvoie un pointeur vers le résultat)
                if(operateurBinaire->toString() == "+")
                    res=(*l2+*l1);
                if(operateurBinaire->toString() == "-")
                    res=(*l2-*l1);
                if(operateurBinaire->toString() == "*")
                    res=(*l2**l1);
                if(operateurBinaire->toString() == "/")
                    res=(*l2 / *l1);
                if(operateurBinaire->toString() == "DIV")
                {
                    isDiv=true;
                    Entier* e1 = dynamic_cast<Entier*>(l1);
                    Entier* e2 = dynamic_cast<Entier*>(l2);

                    if (e1&&e2)
                    {
                        res=DIV(e2,e1);
                        this->empiler(res);;
                        MainWindow::getInstance()->setMsg("Calcul effectué !");
                    }
                    else
                    {
                        Expression* exp1 = dynamic_cast<Expression*>(l2);
                        Expression* exp2 = dynamic_cast<Expression*>(l1);
                        if (exp1||exp2)
                        {
                            std::string result;
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp1 = exp1->toString();
                                temp1=temp1.substr(1,temp1.length()-2);
                                if (exp2)
                                {
                                    std::string temp2 = exp2->toString();
                                    temp2=temp2.substr(1,temp2.length()-2);
                                    result = "'DIV("+temp1+","+temp2+")'";
                                }
                                else
                                {
                                    result = "'DIV("+temp1+","+l1->toString()+")'";
                                }
                            }
                            else
                            {
                                if (exp2)
                                {
                                    std::string temp2 = exp2->toString();
                                    temp2=temp2.substr(1,temp2.length()-2);
                                    result = "'DIV("+l2->toString()+","+temp2+")'";
                                }
                                else
                                {
                                    result = "'DIV("+l2->toString()+","+l1->toString()+")'";
                                }
                            }
                            this->commande(result);
                            MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                        }
                        else
                        {
                            MainWindow::getInstance()->setMsg("Erreur : DIV ne peut s'appliquer que sur deux entiers !");
                            //On re-empile
                            this->empiler(l2);
                            this->empiler(l1);
                        }
                    }
                }

                if(operateurBinaire->toString() == "MOD")
                {
                    isMod=true;
                    Entier* e1 = dynamic_cast<Entier*>(l1);
                    Entier* e2 = dynamic_cast<Entier*>(l2);

                    if (e1&&e2)
                    {
                        res=MOD(e2,e1);
                        this->empiler(res);;
                        MainWindow::getInstance()->setMsg("Calcul effectué !");
                    }
                    else
                    {
                        Expression* exp1 = dynamic_cast<Expression*>(l2);
                        Expression* exp2 = dynamic_cast<Expression*>(l1);
                        if (exp1||exp2)
                        {
                            std::string result;
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp1 = exp1->toString();
                                temp1=temp1.substr(1,temp1.length()-2);
                                if (exp2)
                                {
                                    std::string temp2 = exp2->toString();
                                    temp2=temp2.substr(1,temp2.length()-2);
                                    result = "'MOD("+temp1+","+temp2+")'";
                                }
                                else
                                {
                                    result = "'MOD("+temp1+","+l1->toString()+")'";
                                }
                            }
                            else
                            {
                                if (exp2)
                                {
                                    std::string temp2 = exp2->toString();
                                    temp2=temp2.substr(1,temp2.length()-2);
                                    result = "'MOD("+l2->toString()+","+temp2+")'";
                                }
                                else
                                {
                                    result = "'MOD("+l2->toString()+","+l1->toString()+")'";
                                }
                            }
                            this->commande(result);
                            MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                        }
                        else
                        {
                            MainWindow::getInstance()->setMsg("Erreur : MOD ne peut s'appliquer que sur deux entiers !");
                            //On re-empile
                            this->empiler(l2);
                            this->empiler(l1);
                        }
                    }
                }

                if(operateurBinaire->toString() == "STO")
                {
                    isSto=true;
                    Expression* e1 = dynamic_cast<Expression*>(l1);

                    Expression* test1 = dynamic_cast<Expression*>(l2);
                    Programme* test2 = dynamic_cast<Programme*>(l2);
                    LitteraleNumerique* test3 = dynamic_cast<LitteraleNumerique*>(l2);

                    if (e1->toString()=="'DIV'"||e1->toString()=="'NEG'"||e1->toString()=="'NUM'"||e1->toString()=="'DEN'"||e1->toString()=="'$'"||e1->toString()=="'RE'"||e1->toString()=="'IM'"||e1->toString()=="'AND'"||e1->toString()=="'OR'"||e1->toString()=="'NOT'"||e1->toString()=="'EVAL'"||e1->toString()=="'STO'"||e1->toString()=="'DUP'"||e1->toString()=="'DROP'"||e1->toString()=="'SWAP'"||e1->toString()=="'LASTOP'"||e1->toString()=="'LASTARGS'"||e1->toString()=="'UNDO'"||e1->toString()=="'REDO'"||e1->toString()=="'CLEAR'")
                    {
                        MainWindow::getInstance()->setMsg("Erreur : attention à ne pas donner le nom d'un opérateur comme nom de variable !");
                        //On re-empile
                        this->empiler(l2);
                        this->empiler(l1);
                    }
                    else
                    {
                        if (test1||test2||test3) //Si on cherche bien à stocker une expression, un programme ou une litterale numerique
                        {

                            //Si le premier argument est bien une expression ne comportant qu'un atome,
                            //On ajoute cet atome à AtomeManager en le liant à la litterale
                            if (e1)
                            {
                                std::string temp = e1->toString();
                                int temp1 = e1->toString().length()-2; //taille du string sans les quotes
                                temp = temp.substr(1,temp1); //On retire les quotes
                                Atome* a = new Atome(temp,l2); //On ajoute l'identificateur lié à la variable l1
                                AtomeManager::getInstance().addAtome(a);
                                MainWindow::getInstance()->setMsg("Variable initialisee !");
                            }
                            else
                            {
                                MainWindow::getInstance()->setMsg("Erreur : une variable/expression/programme doit etre liee a une expression contenant un atome !");
                                //On re-empile
                                this->empiler(l2);
                                this->empiler(l1);
                            }
                        }
                        else //Sinon on cherche à stocker autre chose, ce qui est impossible
                        {
                            MainWindow::getInstance()->setMsg("Erreur : l'opérateur STO n'est applicable qu'à une expression, un programme ou une littérale numérique !");
                            //On re-empile
                            this->empiler(l2);
                            this->empiler(l1);
                        }
                    }
                }

                if(operateurBinaire->toString() == "$")
                {
                    isComp=true;
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        res=new Complexe(littNum1,littNum2);
                        this->empiler(res);;
                        MainWindow::getInstance()->setMsg("Complexe bien créé !");
                    }
                    else
                    {
                        Expression* exp1 = dynamic_cast<Expression*>(l2);
                        Expression* exp2 = dynamic_cast<Expression*>(l1);
                        if (exp1||exp2)
                        {
                            std::string result;
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp1 = EVAL(exp1);
                                if (exp2)
                                {
                                    std::string temp2 = EVAL(exp2);
                                    result = temp1+" "+temp2+" $";
                                }
                                else
                                {
                                    result = temp1+" "+l1->toString()+" $";
                                }
                            }
                            else
                            {
                                if (exp2)
                                {
                                    std::string temp2 = EVAL(exp2);
                                    result = l2->toString()+" "+temp2 + " $";
                                }
                                else
                                {
                                    result = l2->toString()+" "+l1->toString()+" $";
                                }
                            }
                            this->commande(result);
                            MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                        }
                        else
                        {
                            MainWindow::getInstance()->setMsg("Erreur : un complexe ne peut être constitué que de variables numeriques (entier, reel ou rationnel)");
                            //On re-empile
                            this->empiler(l2);
                            this->empiler(l1);
                        }
                    }
                }
                if(operateurBinaire->toString() == "=")
                {
                    isEqual=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()==littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Complexe* comp1=dynamic_cast<Complexe*>(l1);
                        Complexe* comp2=dynamic_cast<Complexe*>(l2);
                        if (comp1&&comp2)
                        {
                            if ( (comp1->getReal()->getNb()==comp2->getReal()->getNb()) && (comp1->getImag()->getNb()==comp2->getImag()->getNb()) )
                            {
                                res=new Entier(1);
                                this->empiler(res);;
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l2);
                            Expression* exp2 = dynamic_cast<Expression*>(l1);
                            if (exp1||exp2)
                            {
                                std::string result;
                                if (exp1)
                                {
                                    res=NULL;
                                    std::string temp1 = EVAL(exp1);
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = temp1+" "+temp2+"=";
                                    }
                                    else
                                    {
                                        result = temp1+" "+l1->toString()+" =";
                                    }
                                }
                                else
                                {
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = l2->toString()+" "+temp2 + " =";
                                    }
                                    else
                                    {
                                        result = l2->toString()+" "+l1->toString()+" =";
                                    }
                                }
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);
                            }
                        }
                    }
                }

                if(operateurBinaire->toString() == "!=")
                {
                    isNotEqual=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()!=littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Complexe* comp1=dynamic_cast<Complexe*>(l1);
                        Complexe* comp2=dynamic_cast<Complexe*>(l2);
                        if (comp1&&comp2)
                        {
                            if ( (comp1->getReal()->getNb()!=comp2->getReal()->getNb()) && (comp1->getImag()->getNb()!=comp2->getImag()->getNb()) )
                            {
                                res=new Entier(1);
                                this->empiler(res);;
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l2);
                            Expression* exp2 = dynamic_cast<Expression*>(l1);
                            if (exp1||exp2)
                            {
                                std::string result;
                                if (exp1)
                                {
                                    res=NULL;
                                    std::string temp1 = EVAL(exp1);
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = temp1+" "+temp2+" !=";
                                    }
                                    else
                                    {
                                        result = temp1+" "+l1->toString()+" !=";
                                    }
                                }
                                else
                                {
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = l2->toString()+" "+temp2 + " !=";
                                    }
                                    else
                                    {
                                        result = l2->toString()+" "+l1->toString()+" !=";
                                    }
                                }
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                    }
                }

                if(operateurBinaire->toString() == "<=")
                {
                    isInfOrEqual=true;
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()<=littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Complexe* comp1=dynamic_cast<Complexe*>(l1);
                        Complexe* comp2=dynamic_cast<Complexe*>(l2);
                        if (comp1&&comp2)
                        {
                            if ( (comp1->getReal()->getNb()<=comp2->getReal()->getNb()) && (comp1->getImag()->getNb()<=comp2->getImag()->getNb()) )
                            {
                                res=new Entier(1);
                                this->empiler(res);;
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l2);
                            Expression* exp2 = dynamic_cast<Expression*>(l1);
                            if (exp1||exp2)
                            {
                                std::string result;
                                if (exp1)
                                {
                                    res=NULL;
                                    std::string temp1 = EVAL(exp1);
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = temp1+" "+temp2+" <=";
                                    }
                                    else
                                    {
                                        result = temp1+" "+l1->toString()+" <=";
                                    }
                                }
                                else
                                {
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = l2->toString()+" "+temp2 + " <=";
                                    }
                                    else
                                    {
                                        result = l2->toString()+" "+l1->toString()+" <=";
                                    }
                                }
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                    }
                }

                if(operateurBinaire->toString() == ">=")
                {
                    isSupOrEqual=true;
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()>=littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Complexe* comp1=dynamic_cast<Complexe*>(l1);
                        Complexe* comp2=dynamic_cast<Complexe*>(l2);
                        if (comp1&&comp2)
                        {
                            if ( (comp1->getReal()->getNb()>=comp2->getReal()->getNb()) && (comp1->getImag()->getNb()>=comp2->getImag()->getNb()) )
                            {
                                res=new Entier(1);
                                this->empiler(res);;
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l2);
                            Expression* exp2 = dynamic_cast<Expression*>(l1);
                            if (exp1||exp2)
                            {
                                std::string result;
                                if (exp1)
                                {
                                    res=NULL;
                                    std::string temp1 = EVAL(exp1);
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = temp1+" "+temp2+" >=";
                                    }
                                    else
                                    {
                                        result = temp1+" "+l1->toString()+" >=";
                                    }
                                }
                                else
                                {
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = l2->toString()+" "+temp2 + " >=";
                                    }
                                    else
                                    {
                                        result = l2->toString()+" "+l1->toString()+" >=";
                                    }
                                }
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                    }
                }

                if(operateurBinaire->toString() == "<")
                {
                    isInf=true;
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()<littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Complexe* comp1=dynamic_cast<Complexe*>(l1);
                        Complexe* comp2=dynamic_cast<Complexe*>(l2);
                        if (comp1&&comp2)
                        {
                            if ( (comp1->getReal()->getNb()<comp2->getReal()->getNb()) && (comp1->getImag()->getNb()<comp2->getImag()->getNb()) )
                            {
                                res=new Entier(1);
                                this->empiler(res);;
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l2);
                            Expression* exp2 = dynamic_cast<Expression*>(l1);
                            if (exp1||exp2)
                            {
                                std::string result;
                                if (exp1)
                                {
                                    res=NULL;
                                    std::string temp1 = EVAL(exp1);
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = temp1+" "+temp2+" <";
                                    }
                                    else
                                    {
                                        result = temp1+" "+l1->toString()+" <";
                                    }
                                }
                                else
                                {
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = l2->toString()+" "+temp2 + " <";
                                    }
                                    else
                                    {
                                        result = l2->toString()+" "+l1->toString()+" <";
                                    }
                                }
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                    }
                }

                if(operateurBinaire->toString() == ">")
                {
                    isSup=true;
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()>littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Complexe* comp1=dynamic_cast<Complexe*>(l1);
                        Complexe* comp2=dynamic_cast<Complexe*>(l2);
                        if (comp1&&comp2)
                        {
                            if ( (comp1->getReal()->getNb()>comp2->getReal()->getNb()) && (comp1->getImag()->getNb()>comp2->getImag()->getNb()) )
                            {
                                res=new Entier(1);
                                this->empiler(res);;
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                        else
                        {
                            Expression* exp1 = dynamic_cast<Expression*>(l2);
                            Expression* exp2 = dynamic_cast<Expression*>(l1);
                            if (exp1||exp2)
                            {
                                std::string result;
                                if (exp1)
                                {
                                    res=NULL;
                                    std::string temp1 = EVAL(exp1);
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = temp1+" "+temp2+" >";
                                    }
                                    else
                                    {
                                        result = temp1+" "+l1->toString()+" >";
                                    }
                                }
                                else
                                {
                                    if (exp2)
                                    {
                                        std::string temp2 = EVAL(exp2);
                                        result = l2->toString()+" "+temp2 + " >";
                                    }
                                    else
                                    {
                                        result = l2->toString()+" "+l1->toString()+" >";
                                    }
                                }
                                this->commande(result);
                                MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                            }
                            else
                            {
                                res=new Entier(0);
                                this->empiler(res);;
                            }
                        }
                    }
                }

                if(operateurBinaire->toString() == "AND")
                {
                    isAND=true;
                    Entier* ent1=dynamic_cast<Entier*>(l1);
                    Entier* ent2=dynamic_cast<Entier*>(l2);
                    if (ent1&&ent2)
                    {
                        if (ent1->getNb()==0||ent2->getNb()==0)
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Expression* exp1 = dynamic_cast<Expression*>(l2);
                        Expression* exp2 = dynamic_cast<Expression*>(l1);
                        if (exp1||exp2)
                        {
                            std::string result;
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp1 = EVAL(exp1);
                                if (exp2)
                                {
                                    std::string temp2 = EVAL(exp2);
                                    result = temp1+" "+temp2+" AND";
                                }
                                else
                                {
                                    result = temp1+" "+l1->toString()+" AND";
                                }
                            }
                            else
                            {
                                if (exp2)
                                {
                                    std::string temp2 = EVAL(exp2);
                                    result = l2->toString()+" "+temp2 + " AND";
                                }
                                else
                                {
                                    result = l2->toString()+" "+l1->toString()+" AND";
                                }
                            }
                            this->commande(result);
                            MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                        }
                        else
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                    }
                }

                if(operateurBinaire->toString() == "OR")
                {
                    isOR=true;
                    Entier* ent1=dynamic_cast<Entier*>(l1);
                    Entier* ent2=dynamic_cast<Entier*>(l2);
                    if (ent1&&ent2)
                    {
                        if (ent1->getNb()==0&&ent2->getNb()==0)
                        {
                            res=new Entier(0);
                            this->empiler(res);;
                        }
                        else
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                    }
                    else
                    {
                        Expression* exp1 = dynamic_cast<Expression*>(l2);
                        Expression* exp2 = dynamic_cast<Expression*>(l1);
                        if (exp1||exp2)
                        {
                            std::string result;
                            if (exp1)
                            {
                                res=NULL;
                                std::string temp1 = EVAL(exp1);
                                if (exp2)
                                {
                                    std::string temp2 = EVAL(exp2);
                                    result = temp1+" "+temp2+" OR";
                                }
                                else
                                {
                                    result = temp1+" "+l1->toString()+" OR";
                                }
                            }
                            else
                            {
                                if (exp2)
                                {
                                    std::string temp2 = EVAL(exp2);
                                    result = l2->toString()+" "+temp2 + " OR";
                                }
                                else
                                {
                                    result = l2->toString()+" "+l1->toString()+" OR";
                                }
                            }
                            this->commande(result);
                            MainWindow::getInstance()->setMsg("OK, opération effectuée !");
                        }
                        else
                        {
                            res=new Entier(1);
                            this->empiler(res);;
                        }
                    }
                }
                if(operateurBinaire->toString() == "IFT")
                {
                    isIFT=true;
                    Entier* e2 = dynamic_cast<Entier*>(l2);
                    Expression* exp1 = dynamic_cast<Expression*>(l1);
                    Programme* prog1 = dynamic_cast<Programme*>(l1);
                    if ((e2) && (exp1||prog1))
                    {
                        if (e2->getNb()!=0)
                        {
                            MainWindow::getInstance()->setMsg("Test VRAI");
                            std::string temp = EVAL(l1);
                            this->commande(temp);
                        }
                        else
                        {
                            MainWindow::getInstance()->setMsg("Test FAUX");
                        }
                    }
                    else
                    {
                        this->empiler(l2);
                        this->empiler(l1);
                        MainWindow::getInstance()->setMsg("Erreur : IFT ne peut s'appliquer que sur le test d'un entier d'abord, pour évaluer une expression ou un programme !");
                    }

                }



                if (!isDiv&&!isMod&&!isSto&&!isComp&&!isEqual&&!isNotEqual&&!isInfOrEqual&&!isSupOrEqual&&!isInf&&!isSup&&!isAND&&!isOR&&!isIFT&&res)
                {
                // On met le resultat en haut de pile
                this->empiler(res);;

                MainWindow::getInstance()->setMsg("Calcul effectué !");
                }

                }
                else
                {
                    // Si on arrive ici, c'est qu'il n'y a pas assez d'élément dans la pile
                    MainWindow::getInstance()->setMsg("Erreur : Pas assez d'élément !");
                }
            }


}

/*! \brief Renvoie le contenu de la pile dans un string (les size premiers resultats) */
std::string Controleur::pileString(int size)
{
    // On copie la pile dans une pile tampon
    std::stack<Operande*> tampon = pile;

    // Operande buffer
    Operande* op;

    // Stringstream qui contient la pile
    std::stringstream result;
    int i=0;

    // Tant que le tampon n'est pas vide
    while(!tampon.empty() && i<size)
    {
        // On depile, et on ajoute au string de retour
        op=tampon.top();
        tampon.pop();
        op->afficher(result);
        result<<std::endl;
        i++;
    }
    if(!tampon.empty())
    {
        result<<"..."<<std::endl;
    }
    // Si la pile est vide, on le dit !
    if(result.rdbuf()->in_avail()==0) // Test si result contient des caracteres
        return "Pile vide";
    // Sinon, on renvoie le resultat
    return result.str();
}

/*! \brief Permet la gestion d'un string composé de différentes opérandes separées d'un espace */
void Controleur::commande(std::string cmd)
{

    // D'abord, si l'entrée est une expression ou un programme, il faut enlever les espaces
    unsigned int premier=0;
    unsigned int dernier=0;

    // Si la commande est un programme ou une expression, on sauvegarde la premiere et derniere position du ' ou du [
    for(unsigned int i=0;i<cmd.size();i++)
    {
        // Si on trouve un ', c'est un expression
        if(cmd[i]=='\'')
        {

            premier=i;

            // On cherche donc le dernier '
            for(unsigned int j=cmd.size();j>premier;j--)
            {
                if(cmd[j]=='\'')
                {
                    dernier=j;
                    break;
                }
            }

            // Une fois qu'on a localise le premier et le dernier ', on supprime tous les espaces entre les deux
            for(unsigned int k=premier;k<dernier;k++)
            {
            if(cmd[k]==' ')
                cmd=cmd.erase(k,1);
            }

            break;
        }

        // Si on trouve un [, c'est un programme
        if(cmd[i]=='[')
        {
            premier=i;

            // On cherche donc le ]
            for(unsigned int j=cmd.size();j>premier;j--)
            {
                if(cmd[j]==']')
                {
                    dernier=j;
                    break;
                }
            }

            // Une fois les espaces enlevées,
            // On recupere tout ce qui était avant et on l'envoi à la commande

            std::string avant=cmd.substr(0,premier);
            this->commande(avant);

            // Ensuite on recupere le programme en lui meme
            std::string programme=cmd.substr(premier,dernier-premier+1);
            // Et on l'empile
            this->empiler(FactoryLitterale::getInstance(),programme);

            // Et enfin, on prends ce qui etait apres le programme et on l'envoi à la commande
            std::string suite=cmd.substr(dernier+1,cmd.size()-dernier);
            this->commande(suite);

            // On sort de commande
            return;
        }


    }


    // Le but de cette partie est d'envoyé la ligne de commande en plusieurs fois, en la separant par les espaces
    // Par exemple 3 3 + empilera 3, empilera 3 pour executera +
    std::istringstream iss(cmd);
    std::string sub;
    iss >> sub;

    // Necessaire pour permettre de coller un operateur a une litterale : 1+
    //std::string op="";
    //bool opColle=false;

     while(iss)
     {
         std::string t = sub.c_str();
         // A ce stade, sub contient la partie du string entre des espaces
         // Si ce string est un opérateur, on l'ajoute à l'aide de la FactoryOperateur
         if(estOperateur(t))
         {
             // On se souvient du dernier operateur utiliser pour la fonction lastOP
             if(t!="UNDO" && t!="REDO" && t!="LASTOP")
                this->lastOP=t;
             // On empile l'opérateur
             this->empiler(FactoryOperateur::getInstance(),sub);
             // Et on execute la pile
             this->executer();
         }
         // Sinon, on considere que c'est une litterale
         else
         {
             // On verifie si un operateur n'est pas colle a une litterale (EX : 1+)
             /*for(int i=0;i<sub.size();i++)
             {
                 if(opColle)
                     break;
                 // Si on rencontre qqchose qui n'est pas un chiffre, il y'a un operateur de collé !
                 if(!(sub[i]>=48 && sub[i]<=57))
                 {
                     // La partie avant i est la littérale
                     t = sub.substr(0,i);
                     // La partie apres est l'opérateur
                     op=sub.substr(i,sub.size());
                     opColle=true;
                     break;


                 }
             }*/

             // Dans ce cas on se souvient du dernier arg pour la fonction lastArgs
             this->lastArgs=t;
             // On sauvegarde l'etat pour pouvoir utiliser UNDO REDO
             this->save();
             // On empile
             this->empiler(FactoryLitterale::getInstance(),sub);

             // Si on avait un operateur colle, on l'execute
             //if(opColle)
             //    this->commande(op);
         }

         iss >> sub;
     }

}


/*! \brief Empile une opérande */
void Controleur::empiler(Operande* value ){pile.push(value);}
/*! \brief Empile une valeur donnée gérée par une factory donnéee */
void Controleur::empiler(Factory& facto, std::string value)
{
    Operande* temp = facto.create(value);
    if(temp!=NULL)
    pile.push(temp);
}


//  SINGLETON CONTROLEUR

// Initialisation de l'attribut statique
Controleur::Handler Controleur::handler = Controleur::Handler();

/*! \brief (SINGLETON) */
Controleur& Controleur::getInstance()
{
    if(handler.instance==nullptr) {
    handler.instance=new Controleur;
}
return *handler.instance;
}

/*! \brief (SINGLETON) */
void Controleur::libererInstance()
{
  delete handler.instance;
  handler.instance=nullptr;

}








// SINGLETON CARETAKER

// Initialisation de l'attribut statique
CareTaker::Handler CareTaker::handler = CareTaker::Handler();

// Singleton
CareTaker& CareTaker::getInstance()
{
    if(handler.instance==nullptr) {
    handler.instance=new CareTaker;
}
return *handler.instance;
}


void CareTaker::libererInstance()
{
  delete handler.instance;
  handler.instance=nullptr;

}
