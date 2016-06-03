#include "../manager/controleur.h"
#include "../manager/factory.h"
#include "../litterales/litterales.h"
#include "../litterales/operateurs.h"
#include <string>
#include <sstream>


void Controleur::executer()
{

        // Le premier est un operateur
        Operande* topOperande = pile.top();


        Binaire* monOperateur = dynamic_cast<Binaire*>(topOperande);
        if(monOperateur)
        {
            pile.pop();

        // Si c'est un opérateur binaire, il faut que la pile soit supérieur ou égale à 2
        if(pile.size()>=2)
        {
            Operande* v1 = pile.top();


            Litterale* l1 = dynamic_cast<Litterale*>(v1);

            pile.pop();

            Operande* v2 = pile.top();
            pile.pop();

            Litterale* l2 = dynamic_cast<Litterale*>(v2);

            Litterale* res=(*l1+*l2);


            this->pile.push(res);

        }
        }
        else
        {
            Litterale* l1 = dynamic_cast<Litterale*>(topOperande);

            this->pile.push(l1);

        }

}

std::string Controleur::pileString()
{
    std::stack<Operande*> tampon = pile;
    Operande* op;

    std::stringstream result;


    while(!tampon.empty())
    {
           op=tampon.top();
           tampon.pop();
           op->afficher(result);
           result<<std::endl;
    }

    if(result.rdbuf()->in_avail()==0) // Test si result contient des caracteres
        return "Pile vide";
     return result.str();
}

void Controleur::commande(std::string cmd)
{
    std::istringstream iss(cmd);
    std::string sub;
    iss >> sub;

     while(iss)
     {

         // A ce stade, sub contient la partie du string entre des espaces
         // Si ce string est un opérateur, on l'ajoute à l'aide de la FactoryOperateur
         if(estOperateur(sub))
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


