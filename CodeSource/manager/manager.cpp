#include "../manager/manager.h"
#include <stdlib.h>

// Prends un string en entrée et renvoie un pointeur vers une littérale contenant la valeur attendu
Litterale* FactoryLitterale::addLitterale(std::string litterale)
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

        std::string partieReel;
        std::string partieComplexe;

        std::string partieEntiere;
        std::string partieDecimale;

        std::string numerateur;
        std::string denominateur;


        // On parcours le string
        for(unsigned int i=0;i<litterale.size();i++)
        {
            // Si on trouve un dollar, la littérale est complexe
            if(litterale[i]=='$')
            {
                // On enregistre la position du dollar
                int positionDollar=i;
                isComplexe=true;

                // On separe le string en deux parties qui nous interesse
                partieReel=litterale.substr(0,positionDollar);
                partieComplexe=litterale.substr(positionDollar+1,litterale.size());

                std::cout<<"Litterale complexe ! Partie reele : " << partieReel << " Partie complexe : " << partieComplexe <<std::endl;
            }
            // Si on trouve un point, la littérale est reele
            if(litterale[i]=='.')
            {
                // On enregistre la position du point
                int positionPoint=i;
                isReel=true;

                // On separe le string en deux parties qui nous interesse
                partieEntiere=litterale.substr(0,positionPoint);
                partieDecimale=litterale.substr(positionPoint+1,litterale.size());
                std::cout<<"Litterale reele ! Partie entiere : " << partieEntiere << " Partie decimale : " << partieDecimale <<std::endl;
            }
            // Si on trouve un slash, la littérale est rationnelle
            if(litterale[i]=='/')
            {
                // On enregistre la position du slash
                int positionSlash=i;
                isRationnel=true;

                // On separe le string en deux parties qui nous interesse
                numerateur=litterale.substr(0,positionSlash);
                denominateur=litterale.substr(positionSlash+1,litterale.size());
                std::cout<<"Litterale rationnelle ! Numerateur : " << numerateur << " Numerateur : " << denominateur <<std::endl;
            }
            // Si on trouve un crochet, la littérale est programme
            if(litterale[i]=='[')
            {
                // On enregistre la position du crochet
                int positionCrochet=i;
                isProgramme=true;

                std::cout<<"Litterale programme !"<<std::endl;
            }
        }
        // Il est important de tester complexe avant reel car une littérale complexe peut contenir un reel mais pas l'inverse !
        if(isComplexe==true)
        {
            //Complexe* monComplexe = new Complexe()
            return NULL;
        }
        if(isReel==true)
        {
            Entier* monEntier1=new Entier(atoi(partieEntiere.c_str()));
            Entier* monEntier2= new Entier(atoi(partieDecimale.c_str()));
            Reel* monReel = new Reel(*monEntier1,*monEntier2);
            return monReel;
        }
        if(isRationnel==true)
        {
            return NULL;
        }
        if(isProgramme==true)
        {
            return NULL;
        }

        // Si on est arrivé ici, c'est que la littérale indiqué est un entier
        std::cout<<"Litterale entiere !"<<std::endl;
        int value = atoi(litterale.c_str());
        Entier* monEntier = new Entier(value);
        return monEntier;

    }

}


// Initialisation de l'attribut statique
FactoryLitterale::Handler FactoryLitterale::handler = FactoryLitterale::Handler();

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




