#include "xml_dom.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

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



        QTextStream stream( &xml_doc );
        stream << dom.toString();


    }



xml_doc.close();



}

Xml_Dom::~Xml_Dom()
{

}
QString Xml_Dom::getKeyboard()
{

    xml_doc.open(QIODevice::ReadWrite);

    QDomElement racine = dom.documentElement(); // renvoie la balise racine
    // Parametres
    QDomNode noeud = racine.firstChild();
    QDomElement element;


        element = noeud.toElement();
             xml_doc.close();
        return element.attribute("value");


}
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
