#include "xml_dom.h"

#include <QMessageBox>

/*!
 * \file xml_dom.h
 * \brief Gestion du fichier XML
 * \author Blanquet - Martinache
 * \version 0.1
 */

using namespace std;

/*! \brief Constructeur */
Xml_Dom::Xml_Dom() : QWidget()

{


    xml_doc.setFileName("../XML/param.xml");

    if(xml_doc.exists())
    {

        if(!xml_doc.open(QIODevice::ReadWrite))
        {

            xml_doc.close();

            QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");

            return;

        }
        if (!dom.setContent(&xml_doc))

            {


            xml_doc.close();
             QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");

             return;

            }
    }
    else
    {

        xml_doc.open(QIODevice::ReadWrite | QIODevice::Text);



        QDomElement param = dom.createElement("Parametres");

        dom.appendChild(param);


        QDomElement clavier = dom.createElement("Clavier");
        clavier.setAttribute("value", 1);
        param.appendChild(clavier);



        QDomElement pile = dom.createElement("Pile");
        pile.setAttribute("number", 5);
        param.appendChild(pile);

        QDomElement bip = dom.createElement("BIP");
        bip.setAttribute("activated", 1);
        param.appendChild(bip);

        QTextStream stream( &xml_doc );
        stream << dom.toString();


    }



xml_doc.close();



}
/*! \brief Destructeur */
Xml_Dom::~Xml_Dom()
{

}
/*! \brief Recupere la valeur clavier contenue dans le XML */
QString Xml_Dom::getKeyboard()
{

    xml_doc.open(QIODevice::ReadWrite);
    dom.setContent(&xml_doc);
    QDomElement racine = dom.documentElement(); // renvoie la balise racine
    // Parametres
    QDomNode noeud = racine.firstChild();
    QDomElement element;


        element = noeud.toElement();
                     xml_doc.close();
        return element.attribute("value");



}
/*! \brief Modifie le fichier XML pour mettre clavier à la valeur donnée (1 activé, 0 desactivé) */
void Xml_Dom::setKeyboard(int value)
{

    xml_doc.open(QIODevice::ReadWrite |QFile::Truncate);

    QDomElement racine = dom.documentElement(); // renvoie la balise racine
    // Parametres
    QDomNode noeud = racine.firstChild();
    QDomElement element;

    element = noeud.toElement();
    element.setAttribute("value", value);

    QTextStream stream( &xml_doc);
    stream << dom.toString();

    xml_doc.close();

}
/*! \brief Recupere la valeur longueur de pile contenue dans le XML */
QString Xml_Dom::getPile()
{

    xml_doc.open(QIODevice::ReadWrite);
    dom.setContent(&xml_doc);
    QDomElement racine = dom.documentElement(); // renvoie la balise racine
    // Parametres
    QDomNode noeud = racine.firstChild().nextSibling();
    QDomElement element;


        element = noeud.toElement();
             xml_doc.close();
         return element.attribute("number");




}
/*! \brief Modifie le fichier XML pour mettre la longueur de pile à la valeur donnée */
void Xml_Dom::setPile(int value)
{

    xml_doc.open(QIODevice::ReadWrite |QFile::Truncate);

    QDomElement racine = dom.documentElement(); // renvoie la balise racine
    // Parametres
    QDomNode noeud = racine.firstChild().nextSibling();
    QDomElement element;

    element = noeud.toElement();
    element.setAttribute("number", value);

    QTextStream stream( &xml_doc);
    stream << dom.toString();

    xml_doc.close();
}
/*! \brief Recupere la valeur bip contenue dans le XML */
QString Xml_Dom::getBip()
{

    xml_doc.open(QIODevice::ReadWrite);
    dom.setContent(&xml_doc);
    QDomElement racine = dom.documentElement(); // renvoie la balise racine
    // Parametres
    QDomNode noeud = racine.firstChild().nextSibling().nextSibling();
    QDomElement element;


        element = noeud.toElement();
               xml_doc.close();
        return element.attribute("activated");



}
/*! \brief Modifie le fichier XML pour mettre bip à la valeur donnée (1 activé, 0 desactivé) */
void Xml_Dom::setBip(int value)
{

    xml_doc.open(QIODevice::ReadWrite |QFile::Truncate);

    QDomElement racine = dom.documentElement(); // renvoie la balise racine
    // Parametres
    QDomNode noeud = racine.firstChild().nextSibling().nextSibling();
    QDomElement element;

    element = noeud.toElement();
    element.setAttribute("activated", value);

    QTextStream stream( &xml_doc);
    stream << dom.toString();

    xml_doc.close();
}
