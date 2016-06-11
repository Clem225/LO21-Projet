#include "controleur.h"

#include "../litterales/litterales.h"
#include "../operateurs/operateurs.h"

#include "../GUI/mainwindow.h"

#include <QDebug>
#include <stdio.h>
#include <stdlib.h>


void Controleur::save()
{

    // Memento
    CareTaker& careTaker = CareTaker::getInstance();
    // Sauvegarde
    Controleur::getInstance().setState(Controleur::getInstance().getState());
    careTaker.add(Controleur::getInstance().saveStateToMemento());
    // Number est le nombre d'elemernt (commence à 1) alors que current est l'indice (commence à 0)
    careTaker.current=careTaker.number();

    qDebug() << "SAVE";
    qDebug() << careTaker.number();
    qDebug() << "CURRENT";
    qDebug() << careTaker.current;

}

void Controleur::redo()
{

    // Memento
    CareTaker& careTaker = CareTaker::getInstance();
    qDebug() << "CURRENT est a ";
    qDebug() << careTaker.current;

    qDebug() << "CURRENT passe a ";
        careTaker.current++;
    if(careTaker.current>careTaker.number())
        careTaker.current=careTaker.number()-1;

    qDebug() << careTaker.current;


    this->getStateFromMemento(careTaker.get(careTaker.current));
    MainWindow::getInstance()->refreshPile();

}
void Controleur::undo()
{

    //Operande* test = careTaker.get(careTaker.number()-1).getState().top();

        CareTaker& careTaker = CareTaker::getInstance();


if(careTaker.number()==careTaker.current){
        this->save();
        careTaker.current--;
}

    qDebug() << "CURRENT est a ";
    qDebug() << careTaker.current;
    careTaker.current--;
    qDebug() << "CURRENT passe a ";
    qDebug() << careTaker.current;
    if(careTaker.current<0)
        careTaker.current=0;

    // Memento

    this->getStateFromMemento(careTaker.get(careTaker.current));
    MainWindow::getInstance()->refreshPile();


}

void Controleur::executer()
{



    // On recupere le haut de la pile
    Operande* topOperande = pile.top();
    Operateur* monOperateur = dynamic_cast<Operateur*>(topOperande);



   if(monOperateur->toString() != "UNDO" && monOperateur->toString() != "REDO")
    {
    this->save();
    }




        //Operateur* monOperateur = dynamic_cast<Operateur*>(topOperande);
        // Si c'est un opérateur -> Pas besoin de tester, si c'est une litterale deja empiler avec commande
        //
        //if(monOperateur)
        //{
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
                            this->empiler(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur NUM ne s'applique que sur des rationnels ou des entiers !");
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
                            this->empiler(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur DEN ne s'applique que sur des rationnels ou des entiers !");
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
                            this->empiler(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur RE ne s'app");
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
                            this->empiler(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur RE ne s'app");
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
                            res = new Entier(0);
                            this->empiler(res);;
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
                            if (temp.find("error")!=-1)
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
                        MainWindow::getInstance()->setMsg("Erreur : DIV ne peut s'appliquer que sur deux entiers !");
                        //On re-empile
                        this->empiler(l2);
                        this->empiler(l1);
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
                        MainWindow::getInstance()->setMsg("Erreur : MOD ne peut s'appliquer que sur deux entiers !");
                        //On re-empile
                        this->empiler(l2);
                        this->empiler(l1);
                    }
                }

                if(operateurBinaire->toString() == "STO")
                {
                    isSto=true;
                    Expression* e1 = dynamic_cast<Expression*>(l1);

                    Expression* test1 = dynamic_cast<Expression*>(l2);
                    Programme* test2 = dynamic_cast<Programme*>(l2);
                    LitteraleNumerique* test3 = dynamic_cast<LitteraleNumerique*>(l2);



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
                        MainWindow::getInstance()->setMsg("Erreur : un complexe ne peut être constitué que de variables numeriques (entier, reel ou rationnel)");
                        //On re-empile
                        this->empiler(l2);
                        this->empiler(l1);
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
                            res=new Entier(0);
                            this->empiler(res);;
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
                            res=new Entier(0);
                            this->empiler(res);;
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
                            res=new Entier(0);
                            this->empiler(res);;
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
                            res=new Entier(0);
                            this->empiler(res);;
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
                            res=new Entier(0);
                            this->empiler(res);;
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
                            res=new Entier(0);
                            this->empiler(res);;
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
                        res=new Entier(1);
                        this->empiler(res);;
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
                        res=new Entier(1);
                        this->empiler(res);;
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



                if (!isDiv&&!isMod&&!isSto&&!isComp&&!isEqual&&!isNotEqual&&!isInfOrEqual&&!isSupOrEqual&&!isInf&&!isSup&&!isAND&&!isOR&&!isIFT)
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


       // }
        // Si ce n'est pas un opérateur
        //else
        //{
         //   // Alors c'est une littérale
          //  Litterale* l1 = dynamic_cast<Litterale*>(topOperande);
            // On l'ajoute à la pile
         //   this->empiler(l1);

        //}

}

// Renvoi la pile sous la forme d'un string (uniquement les size premiers resultats)
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

// Permet de separer une commande en différentes opérandes : "3 3 +" empilera 3 puis empilera 3 avant d'empiler + et d'executer la pile
void Controleur::commande(std::string cmd)
{


    unsigned int premier=0;
    unsigned int dernier=0;

    // Si la commande est un programme ou une expression, on sauvegarde la premiere et derniere position
    for(unsigned int i=0;i<cmd.size();i++)
    {
        if(cmd[i]=='\'')
        {

            premier=i;

            for(unsigned int j=cmd.size();j>premier;j--)
            {
                if(cmd[j]=='\'')
                {
                    dernier=j;
                    break;
                }
            }



for(unsigned int k=premier;k<dernier;k++)
{
if(cmd[k]==' ')
    cmd=cmd.erase(k,1);
}


            break;}

        if(cmd[i]=='['){
            premier=i;

            for(unsigned int j=cmd.size();j>premier;j--)
            {
                if(cmd[j]==']')
                {
                    dernier=j;
                    break;
                }
            }

            std::string avant=cmd.substr(0,premier);

            this->commande(avant);
            std::string programme=cmd.substr(premier,dernier-premier+1);

            this->empiler(FactoryLitterale::getInstance(),programme);

            std::string suite=cmd.substr(dernier+1,cmd.size()-dernier);

            this->commande(suite);

            return;

            break;}


    }



    std::istringstream iss(cmd);
    std::string sub;
    iss >> sub;

     while(iss)
     {

         std::string t = sub.c_str();
         // A ce stade, sub contient la partie du string entre des espaces
         // Si ce string est un opérateur, on l'ajoute à l'aide de la FactoryOperateur
         if(estOperateur(t))
         {
             if(t!="UNDO" && t!="REDO" && t!="LASTOP")
                this->lastOP=t;
             this->empiler(FactoryOperateur::getInstance(),sub);
             // SI c'est un opérateur, on execute !
             this->executer();
         }
         // Sinon, on considere que c'est une litterale
         else
         {
            this->lastArgs=t;
            this->save();
            this->empiler(FactoryLitterale::getInstance(),sub);
         }

         iss >> sub;
     }

}

// Initialisation de l'attribut statique
Controleur::Handler Controleur::handler = Controleur::Handler();

// Singleton
Controleur& Controleur::getInstance()
{
    if(handler.instance==nullptr) {
    handler.instance=new Controleur;
}
return *handler.instance;
}


void Controleur::libererInstance()
{
  delete handler.instance;
  handler.instance=nullptr;

}

void Controleur::empiler(Operande* value ){pile.push(value);}
void Controleur::empiler(Factory& facto, std::string value){
    Operande* temp = facto.create(value);
    if(temp!=NULL)
    pile.push(temp);
}






// SINGLETON

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
