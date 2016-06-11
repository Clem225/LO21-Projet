#include "../litterales/litterales.h"

#include "../GUI/mainwindow.h"


/*------Classes AtomeManager------*/


AtomeManager::Handler AtomeManager::handler=AtomeManager::Handler();

AtomeManager& AtomeManager::getInstance()
{
    if (handler.instance==nullptr) handler.instance=new AtomeManager;
    return *handler.instance;
}

void AtomeManager::libererInstance()
{
    delete handler.instance;
    handler.instance=nullptr;
}

void AtomeManager::addAtome(Atome* a)
{
    if (nb==nbMax)
        agrandissementCapacite();
    atoms[nb++]=a;
    //return atoms[nb-1];
}

void AtomeManager::addAtome(std::string name, Litterale* val) {
    Atome* a = new Atome(name,val);
    this->addAtome(a);
}


void AtomeManager::delAtome(Atome* a)
{
    unsigned int i=0;
    while(i<nb && atoms[i]!=a) i++;
    if (i==nb) throw LitteraleException("elimination d'une Expression inexistante");
    delete atoms[i];
    i++;
    while(i<nb) { atoms[i-1]=atoms[i]; i++; }
    nb--;
}


void AtomeManager::delAtome(std::string name)
{
    Atome* corres=nullptr;
    for (AtomeManager::Iterator it = AtomeManager::getInstance().getIterator(); !it.isDone();it.next())
    {
        if (it.current().getAtome()==name) //On a trouvé l'atome dans atomMng
        {
            corres=&it.current();
            break;
        }
    }
    if (corres)
        AtomeManager::getInstance().delAtome(corres);
}

Litterale* AtomeManager::getValeur(std::string name) const
{

    for (AtomeManager::Iterator it = AtomeManager::getInstance().getIterator(); !it.isDone();it.next())
    {
        if (it.current().getAtome()==name) //On a trouvé l'atome dans atomMng
        {
            //corres=&it.current();
            return it.current().getLink();

            break;
        }
    }

    return NULL;
}

void AtomeManager::modifAtome(const std::string oldname, const std::string newname, Litterale* newval)
{
    Atome* corres=nullptr;
    for (AtomeManager::Iterator it = AtomeManager::getInstance().getIterator(); !it.isDone();it.next())
    {
        if (it.current().getAtome()==oldname) //On a trouvé l'atome dans atomMng
        {
            corres=&it.current();
            break;
        }
    }
    if (corres)
    {
        corres->setName(newname);
        corres->setLink(newval);
    }
}

void AtomeManager::agrandissementCapacite()
{
    nbMax=(nbMax+1)*2;
    Atome** newtab=new Atome*[nbMax];
    for(unsigned int i=0; i<nb; i++) newtab[i]=atoms[i];
    Atome** old=atoms;
    atoms=newtab;
    delete old;
}






/*------Classe rationnel------*/

Entier Rationnel::simplification() {
    if (getNum()!=0) {
        /* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
        Denominateur (PGCD) entre le num et le denominateur */
        int num=getNum(), denom=getDenom();
        // on ne travaille qu’avec des valeurs positives...
        if (num<0) num=-num;
        if (denom<0) denom=-denom;
        while(num!=denom)
        {
            if (num>denom) num=num-denom; else denom=denom-num;
        }
        // on divise le num et le denom par le PGCD=a
        setNum(getNum()/num); setDenom(getDenom()/num);
        // si le denom est négatif, on fait passer le signe - au denom
        if (getDenom()<0) { setDenom(-getDenom()); setNum(-getNum()); }

        //Test pour tranformation en Entier. On ne retourne une valeur que si c'est tranformable en entier
        if ((numerateur.getNb()==0) || (denominateur.getNb()==1))
            return Entier(numerateur.getNb());
    }
    else
    {
        setNum(0);
        setDenom(0);
    }

    // En cas d'erreur
    return Entier(0);
}

// Constructeur rationnel
Rationnel::Rationnel(int e1, int e2) {
    if (e2==0)
    {
        MainWindow::getInstance()->setMsg("Erreur : Division par zero !");
        throw "Erreur, division par zero";
    }
    numerateur=e1;
    denominateur=e2;
    simplification();

}


/*------Classe Reel------*/

// Renvoie la partie entiere du reel
int Reel::getEntiere() const {
    long double ent;
    modfl(nb,&ent);
    return ent;
}

// Renvoie la partie decimal du reel
double Reel::getMantisse() const {
    long double ent,v;
    v=modfl(nb,&ent);
    return v;
}

// Change la partie entiere du reel
void Reel::setEntiere(const Entier& e) {
    long double ent,v;
    v=modfl(nb,&ent);
    ent=e.getNb();
    ent+=v;
    nb=ent;
}

// Renvoie la partie decimal du reel
void Reel::setMantisse(const double &e)
{
    long double ent,v;
    v=modfl(nb,&ent);
    v=e;
    ent+=v;
    nb=ent;
}




