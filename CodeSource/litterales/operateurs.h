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

/*!
 * \class Operateur
*/

class Operateur : public Operande
{
private :
    std::string value;
public :
    Operateur(std::string val):value(val){}
    std::string getValue()const {return value;}

};


/*!
 * \class Numerique
*/

class OpNumerique : public Operateur
{
public :
    OpNumerique(std::string value):Operateur(value){}


};

/*!
 * \class Unaire
*/

class Unaire : public OpNumerique
{
public :
    Unaire(std::string value):OpNumerique(value){}
    void afficher(std::ostream& f=std::cout) const {f<<getValue();}

};

/*!
 * \class Binaire
*/

class Binaire : public OpNumerique
{
public :
    Binaire(std::string value):OpNumerique(value){}
    void afficher(std::ostream& f=std::cout) const {f<<getValue();}
};


#endif // OPERATEURS
