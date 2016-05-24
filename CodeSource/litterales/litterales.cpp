#include "litterales.h"


/*------Classe rationnel------*/

Entier Rationnel::simplification() {
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

// Constructeur rationnel
Rationnel::Rationnel(int e1, int e2) {
    if (e2==0) throw "Erreur, division par zero";
    numerateur=e1;
    denominateur=e2;
    simplification();
}




/*------Classe Reel------*/

double Reel::getNb() const {
    double temp=mantisse.getNb();
    while (temp>1)
        temp/=10;
    if (entiere.getNb()>0)
        return entiere.getNb()+temp;
    else
        return entiere.getNb()-temp;
}


void Reel::setNb(double d) {
    int i=d;
    unsigned int j=0, n=0;
    double temp=d, intToDouble;
    while (intToDouble!=temp)
    {
        temp*=10;
        j++; //Représente le nombre de chiffres après la virgule
        i=temp;
        intToDouble=i;
    }
    temp=d;
    while (temp>1)
    {
        temp/=10;
        n++; //Représente le nombre de chiffres avant la virgule
    }
    std::string s = std::to_string(i);
    std::string partieentiere;
    std::string partiemantisse;
    for (unsigned int k1=0;k1<n;k1++)
        partieentiere[k1]=s[k1];
    for (unsigned int k2=0;k2<j;k2++)
        partiemantisse[k2]=s[n+1+k2];
    setEntiere(stoi(partieentiere));
    setMantisse(stoi(partiemantisse));
}






