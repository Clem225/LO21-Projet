#include "../manager/manager.h"
#include "../litterales/litterales.h"
#include <string>

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
            LitteraleNumerique* litReel = dynamic_cast<LitteraleNumerique*>(this->addLitterale(partieReel));
            LitteraleNumerique* litComplexe = dynamic_cast<LitteraleNumerique*>(this->addLitterale(partieComplexe));

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

void executer()
{


}
bool estUnOperateurBinaire(const std::string& c)
{
    if(c=="+") return true;
    if(c=="-") return true;
    if(c=="*") return true;
    if(c=="/") return true;

    return false;
}

void Controleur::commande(const std::string& c)
{



    if(estUnOperateurBinaire(c))
    {
        // Si c'est un opérateur binaire, il faut que la pile soit supérieur ou égale à 2
        if(pile.size()>=2)
        {
            Operande* v1 = pile.top();
            pile.pop();

            Litterale* l1 = dynamic_cast<Litterale*>(v1);

            // On recupere maintenant le bon type de l'objet
/*
            Programme* prog1 = dynamic_cast<Programme*>(v1); // Si le dynamique cast vaut NULL, ce n'est pas la bon type, sinon OK
            Expression* expr1 = dynamic_cast<Expression*>(v1);
            Atome* atom1 = dynamic_cast<Atome*>(v1);
            Complexe* comp1 = dynamic_cast<Complexe*>(v1);
            Reel* reel1 = dynamic_cast<Reel*>(v1);
            Rationnel* ratio1 = dynamic_cast<Rationnel*>(v1);
            Entier* ent1 = dynamic_cast<Entier*>(v1);

            Litterale* part1;

            if(prog1!=NULL)
            {
                Programme* part1=prog1;
            }
            else if(expr1!=NULL)
            {
                Expression* part1=expr1;
            }
            else if(atom1!=NULL)
            {
                Atome* part1=atom1;
            }
            else if(comp1!=NULL)
            {
                Complexe* part1=comp1;
            }
            else if(reel1!=NULL)
            {
                Reel* part1=reel1;
            }
            else if(ratio1!=NULL)
            {
                Rationnel* part1=ratio1;
            }
            else if(ent1!=NULL)
            {
                Entier* part1=ent1;
            }
*/
            Operande* v2 = pile.top();
            pile.pop();

            Litterale* l2 = dynamic_cast<Litterale*>(v2);


            Litterale& res = *l1+*l2;

            std::cout<<"RESULT : ";
            res.afficher();

            /*if(c=="+") res = *v1+*v2;
            if(c=="-") res = v1-v2;
            if(c=="*") res = v1*v2;
            if(c=="/") res = v1/v2;*/

        }
        else
        {
            throw LitteraleException("Pas assez d element(s) !.\n");
        }

    }

}



