#include "../manager/manager.h"
#include "../litterales/litterales.h"
#include "../litterales/operateurs.h"
#include <string>

// Prends un string en entrée et renvoie un pointeur vers une littérale contenant la valeur attendu
Operande *FactoryLitterale::create(std::string litterale)
{
    // Si le string est vide, on lance une exception
    if(litterale.empty())
    {
        throw LitteraleException("Litterale vide.\n");
    }
    else
    {
        // On cree des boolens pour trouver le type entré
        // /!\ Le type peut etre complexe et reel à la fois !
        bool isComplexe=false;
        bool isReel=false;
        bool isRationnel=false;
        bool isProgramme=false;
        bool isAtome=false;

        bool isExpression=false;

        std::string partieReel;
        std::string partieComplexe;

        std::string partieEntiere;
        std::string partieDecimale;

        std::string numerateur;
        std::string denominateur;

        int positionDollar;
        int positionPoint1;
        //int positionPoint2;
        int positionSlash;

        ///////////////////////////////////////////////////////
        // Début de la detection du type                     //
        ///////////////////////////////////////////////////////

        // Si on trouve un crochet en premiere position, la littérale est programme
        if(litterale[0]=='[')
        {
            isProgramme=true;
        }
        if(litterale[0]>=65 && litterale[0]<=90)
        {
            isAtome=true;
        }
        if(litterale[0]=='\'')
        {
            isExpression=true;
        }
        // On parcours le string
        for(unsigned int i=0;i<litterale.size();i++)
        {
            // Si on trouve un dollar, la littérale est complexe
            if(litterale[i]=='$')
            {
                isComplexe=true;
                // On enregistre la position du dollar
                positionDollar=i;
            }
            // Si on trouve un point, la littérale est reele
            if(litterale[i]=='.')
            {
                isReel=true;
                // On enregistre la position du point
                positionPoint1=i;
            }
            // Si on trouve un slash, la littérale est rationnelle
            if(litterale[i]=='/')
            {
                isRationnel=true;
                // On enregistre la position du slash
                positionSlash=i;

            }

        }

        ///////////////////////////////////////////////////////
        // Fin de la detection du type                       //
        ///////////////////////////////////////////////////////

        // Seul un programme peut commencer par un crochet, on est sur du type
        if(isProgramme==true)
        {
            return NULL;
        }
        // Seul un atome peut commencer par une majuscule, on est sur du type
        if(isAtome==true)
        {
            Atome* monAtome = new Atome(litterale);
            return monAtome;
        }
        // Seule une expression peut commencer par un ', on est sur du type
        if(isExpression==true)
        {
            return NULL;
        }
        // Seul un complexe peut contenir un $, on est sur du type
        if(isComplexe==true)
        {
            // On separe le string en deux parties qui nous interesse

            partieReel=litterale.substr(0,positionDollar);
            partieComplexe=litterale.substr(positionDollar+1,litterale.size());
            LitteraleNumerique* litReel = dynamic_cast<LitteraleNumerique*>(this->create(partieReel));
            LitteraleNumerique* litComplexe = dynamic_cast<LitteraleNumerique*>(this->create(partieComplexe));

            Complexe* monComplexe = new Complexe(litReel,litComplexe);
            return monComplexe;

        }
        // Seul un rationnel peut contenir un /, on est sur du type
        if(isRationnel==true)
        {


            // On separe le string en deux parties qui nous interesse
            numerateur=litterale.substr(0,positionSlash);
            denominateur=litterale.substr(positionSlash+1,litterale.size());

            Rationnel* monRationnel = new Rationnel(atoi(numerateur.c_str()),atoi(denominateur.c_str()));

            return monRationnel;
        }

        // ATTENTION : Ici, on est plus sur du type, en effet, un complexe peut contenir un point, comme un reel ou bien meme un programme ...
        // MAIS comme toutes les autres possibilités ont étaient epuises, on est sur que c'est un reel !
        if(isReel==true)
        {
            Reel* monReel = new Reel(stod(litterale));
            return monReel;
        }            

        // Si on est arrivé ici, c'est que la littérale indiqué est un entier
        int value = atoi(litterale.c_str());
        Entier* monEntier = new Entier(value);
        return monEntier;

    }

}


// Initialisation de l'attribut statique
FactoryLitterale::Handler FactoryLitterale::handler = FactoryLitterale::Handler();

// Singleton
FactoryLitterale& FactoryLitterale::getInstance()
{
    if(handler.instance==nullptr) {
    handler.instance=new FactoryLitterale;
}
return *handler.instance;
}


void FactoryLitterale::libererInstance()
{
  delete handler.instance;
  handler.instance=nullptr;

}


bool estUnOperateurBinaire(const std::string& c)
{
    if(c=="+") return true;
    if(c=="-") return true;
    if(c=="*") return true;
    if(c=="/") return true;

    return false;
}

void Controleur::executer()
{

    std::cout << "COUCOU";


        // Le premier est un operateur
        Operande* monOperateur = pile.top();
        pile.pop();

        monOperateur->afficher();

        Binaire* monOperateurOK = dynamic_cast<Binaire*>(monOperateur);

        // Si c'est un opérateur binaire, il faut que la pile soit supérieur ou égale à 2
        if(pile.size()>=2)
        {
            Operande* v1 = pile.top();
            pile.pop();

            Litterale* l1 = dynamic_cast<Litterale*>(v1);


            Operande* v2 = pile.top();
            pile.pop();

            Litterale* l2 = dynamic_cast<Litterale*>(v2);


            Litterale& res = *l1+*l2;

            std::cout<<"RESULT : ";
            res.afficher();



    }

}


// Prends un string en entrée et renvoie un pointeur vers une littérale contenant la valeur attendu
Operande* FactoryOperateur::create(std::string operateur)
{


    Binaire* monOp = new Binaire("+");
    return monOp;


}


// Initialisation de l'attribut statique
FactoryOperateur::Handler FactoryOperateur::handler = FactoryOperateur::Handler();

// Singleton
FactoryOperateur& FactoryOperateur::getInstance()
{
    if(handler.instance==nullptr) {
    handler.instance=new FactoryOperateur;
}
return *handler.instance;
}


void FactoryOperateur::libererInstance()
{
  delete handler.instance;
  handler.instance=nullptr;

}



