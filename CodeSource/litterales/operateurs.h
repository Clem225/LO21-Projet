#ifndef OPERATEURS
#define OPERATEURS

#include <math.h>
#include <limits>
#include <iostream>
#include "litterales.h"

/*!
 * \file operateurs.h
 * \brief Implementation des operateurs
 * \author Blanquet - Martinache
 * \version 0.1
 */


/*! \brief Verifie si str est un opérateur */
bool estOperateur(std::string& str);
/*! \brief Verifie si str est un opérateur numérique unaire */
bool estUnOperateurUnaire(std::string& c);
/*! \brief Verifie si str est un opérateur numérique binaire */
bool estUnOperateurBinaire(std::string& c);

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
