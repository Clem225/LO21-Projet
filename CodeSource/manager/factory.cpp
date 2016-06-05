#include "../operateurs/operateurs.h"
#include "factory.h"

#include <QString>



// Prends un string en entrée et renvoie un pointeur vers une littérale contenant la valeur attendu
Operande* FactoryOperateur::create(std::string operateur)
{

    if(estOperateur(operateur))
    {
        if(estUnOperateurUnaire(operateur))
        {
            Unaire* monOp = new Unaire(operateur);
            return monOp;
        }
        if(estUnOperateurBinaire(operateur))
        {
            Binaire* monOp = new Binaire(operateur);
            return monOp;
        }
        throw LitteraleException("Erreur lors de la création");

    }
    else
    {
        throw LitteraleException("Operateur invalide");
    }

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
            Expression* monExpression = new Expression(litterale);
            return monExpression;
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
            // ATTENTION : stod ne marche plus avec Qt, il faut utiliser toDouble() de QString !
            QString value = QString::fromStdString(litterale);

            Reel* monReel = new Reel(value.toDouble());
            std::cout<<"Creation reel : ";
            monReel->afficher();
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
