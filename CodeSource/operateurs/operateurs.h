#ifndef OPERATEURS
#define OPERATEURS

#include <iostream>
#include "../litterales/litterales.h"
#include <sstream>
#include "../manager/factory.h"

/*!
 * \file operateurs.h
 * \brief Implementation des operateurs
 * \author Blanquet - Martinache
 * \version 0.1
 */

/*! \brief Verifie si str est un opérateur numérique unaire */
bool estUnOperateurUnaire(const std::string& c);
/*! \brief Verifie si str est un opérateur numérique binaire */
bool estUnOperateurBinaire(const std::string& c);
/*! \brief Verifie si str est un opérateur */
bool estOperateur(const std::string& str);
/*! \brief La fonction DIV effectue la division entiere entre deux entiers */
Entier* DIV(Entier* e1, Entier* e2);
/*! \brief La fonction MOD renvoie le reste de la division entre deux entiers */
Entier* MOD(Entier* e1, Entier* e2);
/*! \brief La fonction MOD renvoie le reste de la division entre deux entiers */
std::string EVAL(Expression& expr);


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
    std::string getValue()const {return value;}

};


/*!
 * \class Numerique
*/
class OpNumerique : public Operateur
{
public :
    /*! \brief Constructeur */
    OpNumerique(std::string value):Operateur(value){}


};

/*!
 * \class Unaire
*/
class Unaire : public OpNumerique
{
public :
    /*! \brief Constructeur */
    Unaire(std::string value):OpNumerique(value){}
    void afficher(std::ostream& f=std::cout) const {f<<getValue();}

};

/*!
 * \class Binaire
*/
class Binaire : public OpNumerique
{
public :
    /*! \brief Constructeur */
    Binaire(std::string value):OpNumerique(value){}
    void afficher(std::ostream& f=std::cout) const {f<<getValue();}
};


#endif // OPERATEURS
