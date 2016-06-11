#ifndef OPERATEURS
#define OPERATEURS

#include <iostream>
#include <sstream>

#include "../litterales/litterales.h"
#include "../manager/factory.h"

/*!
 * \file operateurs.h
 * \brief Implementation des operateurs
 * \author Blanquet - Martinache
 * \version 0.1
 */
/*! \brief Verifie si str est un opérateur zero */
bool estUnOperateurZero(const std::string& c);
/*! \brief Verifie si str est un opérateur unaire */
bool estUnOperateurUnaire(const std::string& c);
/*! \brief Verifie si str est un opérateur binaire */
bool estUnOperateurBinaire(const std::string& c);
/*! \brief Verifie si str est un opérateur */
bool estOperateur(const std::string& str);
/*! \brief La fonction DIV effectue la division entiere entre deux entiers */
Entier* DIV(Entier* e1, Entier* e2);
/*! \brief La fonction MOD renvoie le reste de la division entre deux entiers */
Entier* MOD(Entier* e1, Entier* e2);
/*! \brief La fonction MOD renvoie le reste de la division entre deux entiers */
std::string EVAL(Litterale* litt);


/*!
 * \class Operateur
*/
class Operateur : public Operande
{
private :
    std::string value;
public :
    /*! \brief Constructeur */
    Operateur(std::string val):value(val){}
    Operateur(const Operateur& o):value(o.value){}
    std::string toString()const {return value;}
Operande* clone() const {return new Operateur(*this);}
};
/*!
 * \class Zero
*/
class Zero : public Operateur
{
public :
    /*! \brief Constructeur */
    Zero(std::string value):Operateur(value){}
        Zero(const Zero& o):Operateur(o){}
    Operande* clone() const {return new Zero(*this);}
};

/*!
 * \class Unaire
*/
class Unaire : public Operateur
{
public :
    /*! \brief Constructeur */
    Unaire(std::string value):Operateur(value){}
        Unaire(const Unaire& o):Operateur(o){}
    Operande* clone() const {return new Unaire(*this);}
};

/*!
 * \class Binaire
*/
class Binaire : public Operateur
{
public :
    /*! \brief Constructeur */
    Binaire(std::string value):Operateur(value){}
        Binaire(const Binaire& o):Operateur(o){}
    Operande* clone() const {return new Binaire(*this);}
};


#endif // OPERATEURS
