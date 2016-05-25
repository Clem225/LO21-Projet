#include "litterales.h"
#include "operateurs.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>

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


void Reel::setNb(long double d) {

    long double dTemp=d;
    long double v, e;
    v=modfl(dTemp,&e);

    int j=0;
    while(!areSame(dTemp,e))
    {
        j++;
        dTemp*=10;
        v=modfl(dTemp,&e);

    }
    dTemp=d;
    int n=0;
    while (dTemp>1)
    {
        dTemp/=10;
        n++; //Représente le nombre de chiffres avant la virgule
    }

    std::string s=std::to_string(d);

    std::string partieentiere = s.substr(0,n);
    std::string partiemantisse = s.substr(n+1,n+j);


    int a = stoi(partieentiere);
    int b = stoi(partiemantisse);

    setEntiere(a);
    setMantisse(b);
}




