#include "controleur.h"
#include "../litterales/litterales.h"
#include "../operateurs/operateurs.h"
#include "../GUI/mainwindow.h"
#include <sstream>
#include <string>

void Controleur::executer()
{

        // On recupere le haut de la pile
        Operande* topOperande = pile.top();

        // Si c'est un opérateur
        Operateur* monOperateur = dynamic_cast<Operateur*>(topOperande);
        if(monOperateur)
        {
            // On l'enleve de la pile
            pile.pop();
            // On verifie son arite
            Unaire* operateurUnaire = dynamic_cast<Unaire*>(monOperateur);
            Binaire* operateurBinaire = dynamic_cast<Binaire*>(monOperateur);

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

                    if(operateurUnaire->getValue() == "NEG")
                    {
                        res=l1->NEG();
                        this->pile.push(res);
                    }

                    if(operateurUnaire->getValue() == "NUM")
                    {
                        Rationnel* r1 = dynamic_cast<Rationnel*>(l1);
                        Entier* e1 = dynamic_cast<Entier*>(l1);
                        if (r1||e1)
                        {
                            if (r1)
                                res= new Entier(r1->getNum());
                            if (e1)
                                res=e1;
                            this->pile.push(res);
                            MainWindow::getInstance()->setMsg("NUM bien effectué !");
                        }
                        else
                        {
                            this->pile.push(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur NUM ne s'applique que sur des rationnels ou des entiers !");
                        }
                    }

                    if(operateurUnaire->getValue() == "DEN")
                    {
                        Rationnel* r1 = dynamic_cast<Rationnel*>(l1);
                        Entier* e1 = dynamic_cast<Entier*>(l1);
                        if (r1||e1)
                        {
                            if (r1)
                                res= new Entier(r1->getDenom());
                            if (e1)
                                res= new Entier(1);
                            this->pile.push(res);
                            MainWindow::getInstance()->setMsg("DEN bien effectué !");
                        }
                        else
                        {
                            this->pile.push(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur DEN ne s'applique que sur des rationnels ou des entiers !");
                        }
                    }
                    if(operateurUnaire->getValue() == "RE")
                    {
                        Complexe* c1 = dynamic_cast<Complexe*>(l1);
                        LitteraleNumerique* littNum = dynamic_cast<LitteraleNumerique*>(l1);
                        if (c1||littNum)
                        {
                            if (c1)
                            {
                               res = c1->getReal();
                               this->pile.push(res);
                               MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                            if (littNum)
                            {
                                this->pile.push(littNum);
                                MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                        }
                        else
                        {
                            this->pile.push(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur RE ne s'app");
                        }
                    }
                    if(operateurUnaire->getValue() == "IM")
                    {
                        Complexe* c1 = dynamic_cast<Complexe*>(l1);
                        LitteraleNumerique* littNum = dynamic_cast<LitteraleNumerique*>(l1);
                        if (c1||littNum)
                        {
                            if (c1)
                            {
                               res = c1->getImag();
                               this->pile.push(res);
                               MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                            if (littNum)
                            {
                                res=new Entier(0);
                                this->pile.push(res);
                                MainWindow::getInstance()->setMsg("RE bien effectué !");
                            }
                        }
                        else
                        {
                            this->pile.push(l1);
                            MainWindow::getInstance()->setMsg("Erreur : l'operateur RE ne s'app");
                        }
                    }

                    if(operateurUnaire->getValue() == "NOT")
                    {
                        Entier* ent=dynamic_cast<Entier*>(l1);
                        if (ent)
                        {
                            if (ent->getNb()==0)
                            {
                                res = new Entier(1);
                                this->pile.push(res);
                            }
                            else
                            {
                                res = new Entier(0);
                                this->pile.push(res);
                            }
                        }
                        else
                        {
                            res = new Entier(0);
                            this->pile.push(res);
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
                // On cree un pointeur vers le resultat
                Litterale* res = 0;
                // On fait le calcul correspondant à l'opérateur (qui renvoie un pointeur vers le résultat)
                if(operateurBinaire->getValue() == "+")
                    res=(*l2+*l1);
                if(operateurBinaire->getValue() == "-")
                    res=(*l2-*l1);
                if(operateurBinaire->getValue() == "*")
                    res=(*l2**l1);
                if(operateurBinaire->getValue() == "/")
                    res=(*l2 / *l1);
                if(operateurBinaire->getValue() == "DIV")
                {
                    isDiv=true;
                    Entier* e1 = dynamic_cast<Entier*>(l1);
                    Entier* e2 = dynamic_cast<Entier*>(l2);

                    if (e1&&e2)
                    {
                        res=DIV(e2,e1);
                        this->pile.push(res);
                        MainWindow::getInstance()->setMsg("Calcul effectué !");
                    }
                    else
                    {
                        MainWindow::getInstance()->setMsg("Erreur : DIV ne peut s'appliquer que sur deux entiers !");
                        //On re-empile
                        this->pile.push(l2);
                        this->pile.push(l1);
                    }
                }

                if(operateurBinaire->getValue() == "MOD")
                {
                    isMod=true;
                    Entier* e1 = dynamic_cast<Entier*>(l1);
                    Entier* e2 = dynamic_cast<Entier*>(l2);

                    if (e1&&e2)
                    {
                        res=MOD(e2,e1);
                        this->pile.push(res);
                        MainWindow::getInstance()->setMsg("Calcul effectué !");
                    }
                    else
                    {
                        MainWindow::getInstance()->setMsg("Erreur : MOD ne peut s'appliquer que sur deux entiers !");
                        //On re-empile
                        this->pile.push(l2);
                        this->pile.push(l1);
                    }
                }

                if(operateurBinaire->getValue() == "STO")
                {
                    isSto=true;
                    Expression* e2 = dynamic_cast<Expression*>(l2);

                    //Si le deuxieme argument est bien une expression ne comportant qu'un atome,
                    //On ajoute cet atome à AtomeManager en le liant à la litterale
                    if (e2)
                    {
                        std::string temp = e2->getExpr();
                        int temp2 = e2->getExpr().length()-2; //taille du string sans les quotes
                        temp = temp.substr(1,temp2); //On retire les quotes
                        Atome* a = new Atome(temp,l1); //On ajoute l'identificateur lié à la variable l1
                        AtomeManager::getInstance().addAtome(a);
                        MainWindow::getInstance()->setMsg("Variable initialisee !");
                    }
                    else
                    {
                        MainWindow::getInstance()->setMsg("Erreur : une variable doit etre liee a une expression contenant un atome !");
                        //On re-empile
                        this->pile.push(l2);
                        this->pile.push(l1);
                    }
                }

                if(operateurBinaire->getValue() == "$")
                {
                    isComp=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        res=new Complexe(littNum1,littNum2);
                        this->pile.push(res);
                        MainWindow::getInstance()->setMsg("Complexe bien créé !");
                    }
                    else
                    {
                        MainWindow::getInstance()->setMsg("Erreur : un complexe ne peut être constitué que de variables numeriques (entier, reel ou rationnel)");
                        //On re-empile
                        this->pile.push(l2);
                        this->pile.push(l1);
                    }
                }
                if(operateurBinaire->getValue() == "=")
                {
                    isEqual=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()==littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
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
                                this->pile.push(res);
                            }
                            else
                            {
                                res=new Entier(0);
                                this->pile.push(res);
                            }
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                    }
                }

                if(operateurBinaire->getValue() == "!=")
                {
                    isNotEqual=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()!=littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
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
                                this->pile.push(res);
                            }
                            else
                            {
                                res=new Entier(0);
                                this->pile.push(res);
                            }
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                    }
                }

                if(operateurBinaire->getValue() == "<=")
                {
                    isInfOrEqual=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()<=littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
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
                                this->pile.push(res);
                            }
                            else
                            {
                                res=new Entier(0);
                                this->pile.push(res);
                            }
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                    }
                }

                if(operateurBinaire->getValue() == ">=")
                {
                    isSupOrEqual=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()>=littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
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
                                this->pile.push(res);
                            }
                            else
                            {
                                res=new Entier(0);
                                this->pile.push(res);
                            }
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                    }
                }

                if(operateurBinaire->getValue() == "<")
                {
                    isInf=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()<littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
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
                                this->pile.push(res);
                            }
                            else
                            {
                                res=new Entier(0);
                                this->pile.push(res);
                            }
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                    }
                }

                if(operateurBinaire->getValue() == ">")
                {
                    isSup=true;
                    LitteraleNumerique* littNum1=dynamic_cast<LitteraleNumerique*>(l1);
                    LitteraleNumerique* littNum2=dynamic_cast<LitteraleNumerique*>(l2);
                    if (littNum1&&littNum2)
                    {
                        if (littNum1->getNb()>littNum2->getNb())
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
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
                                this->pile.push(res);
                            }
                            else
                            {
                                res=new Entier(0);
                                this->pile.push(res);
                            }
                        }
                        else
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                    }
                }

                if(operateurBinaire->getValue() == "AND")
                {
                    isAND=true;
                    Entier* ent1=dynamic_cast<Entier*>(l1);
                    Entier* ent2=dynamic_cast<Entier*>(l2);
                    if (ent1&&ent2)
                    {
                        if (ent1->getNb()==0||ent2->getNb()==0)
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                    }
                    else
                    {
                        res=new Entier(1);
                        this->pile.push(res);
                    }
                }

                if(operateurBinaire->getValue() == "OR")
                {
                    isOR=true;
                    Entier* ent1=dynamic_cast<Entier*>(l1);
                    Entier* ent2=dynamic_cast<Entier*>(l2);
                    if (ent1&&ent2)
                    {
                        if (ent1->getNb()==0&&ent2->getNb()==0)
                        {
                            res=new Entier(0);
                            this->pile.push(res);
                        }
                        else
                        {
                            res=new Entier(1);
                            this->pile.push(res);
                        }
                    }
                    else
                    {
                        res=new Entier(1);
                        this->pile.push(res);
                    }
                }



                if (!isDiv&&!isMod&&!isSto&&!isComp&&!isEqual&&!isNotEqual&&!isInfOrEqual&&!isSupOrEqual&&!isInf&&!isSup&&!isAND&&!isOR)
                {
                // On met le resultat en haut de pile
                this->pile.push(res);

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
        // Si ce n'est pas un opérateur
        else
        {
            // Alors c'est une littérale
            Litterale* l1 = dynamic_cast<Litterale*>(topOperande);
            // On l'ajoute à la pile
            this->pile.push(l1);

        }

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
             this->empiler(FactoryOperateur::getInstance(),sub);
             // SI c'est un opérateur, on execute !
             this->executer();
         }
         // Sinon, on considere que c'est une litterale
         else
         {
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


