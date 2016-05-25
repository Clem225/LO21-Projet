#include "litterales.h"
#include "operateurs.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <limits>

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

// Applique la mantisse donne au reel
void Reel::setMantisse(const Entier& e)
{
    // Si la mantisse est negative et que la partie entiere n'est pas nul
    if(e.getNb()<0 && this->getEntiere()!=0)
    {
        // On decale le signe - sur la partie entiere
        mantisse=-e.getNb();
        entiere=-this->getEntiere();
        this->setEntiere(entiere);
    }
    else
        // Sinon, la mantisse peut etre negative
        mantisse=e;
}

// Renvoie un double à partir d'un objet reel
double Reel::getNb() const {
    // On recupere la mantisse
    double temp=mantisse.getNb();
    // On divise la mantisse jusqu'a rendre sa valeur absolu inferieur à 1
    while (abs(temp)>=1)
        temp/=10;
    // Si la partie entiere est vide
    if (entiere.getNb()==0)
    {
        // On renvoie simplement la mantisse
        return temp;
    }
    // Si la valeur est positive
    if (entiere.getNb()>0)
        // On renvoie la partie entiere + la mantisse
        return entiere.getNb()+temp;
    else
        // Sinon on renvoie la partie entiere - la mantisse
        return entiere.getNb()-temp;
}

// Rempli un objet Reel à partir d'un double
void Reel::setNb(long double d) {

    // On garde la valeur de d en mémoire tampon
    long double dTemp=d;
    // V stocke 0.[partie decimal]
    // e stocke la partie entiere
    long double v=0, e=0;
    v=modfl(dTemp,&e);

    // On verifie si la partie entiere n'est pas = à 0
    bool isWithoutInt=false;
    if(e==0)
    {
    isWithoutInt=true;
    }

    // On verifie si la partie decimal n'est pas = à 0
    bool isWithoutDecimal=false;
    if(v==0)
    {
    isWithoutDecimal=true;
    }

    // Compte le nombre de digit avant la virgule -> n
    int n=0;
    while (abs(dTemp)>=1)
    {
        dTemp/=10;
        n++;
    }

    //  On met d dans un string
    std::string s=std::to_string(d);
    std::string partieentiere;

    // Si d est negatif, il faut prendre en compte le moins. On decale la partie entiere de 1
    if(d<0)n++;
    // Si d est negatif mais aussi sans int, il faut encore rajouter un pour prendre en compte le 0
    if(d<0 && isWithoutInt){n++;}


    // Si d ne possede pas de partie decimal...
    if(isWithoutDecimal)
        // Alors la partie entiere est constitue de tout le nombre
        partieentiere=s;
    else
        // Sinon, on prends la partie entre le début et l'emplacement de la virgule
         partieentiere = s.substr(0,n);

    std::string partiemantisse;
    // Si le nombre possede une partie entiere = à 0
    if(isWithoutInt)
        // Alors, si la mantisse est negative
        if(d<0)
            //La mantisse commence à la troisieme position -0.[mantisse]
            partiemantisse = s.substr(3,s.size());
        else
            // Sinon la mantisse commence à la deuxieme position 0.[mantisse]
            partiemantisse = s.substr(2,s.size());
    else
        //  Et si la partieentiere est difference de 0, alors la mantisse commence après la virtgule !
        partiemantisse = s.substr(n+1,s.size());

    // On veut maintenant recuperer nos valeurs dans des ints pour les stocker sous forme d'entier.
    // On commence par la mantisse
    int b;
    // Si il n'y a pas de decimal
    if(isWithoutDecimal)
        // La mantisse est nulle
        b=0;
    else
        // Sinon, on convertit la partiemantisse precedemment obtenue
        b = stoi(partiemantisse);

    // Maintenant la partie entiere
    int a;
    // Si il n'y a pas de partie entiere
    if(isWithoutInt)
    {
        // Alors la a = 0
        a= 0;
        // Si le chiffre était negatif, on doit alors decaler le signe - dans la mantisse
        if(d<0)
         b=-b;
    }
    else
        // Sinon, on effectue la conversion
        a = stoi(partieentiere);

    // On change le reel !
    setEntiere(a);
    setMantisse(b);
}




