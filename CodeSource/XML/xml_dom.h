#ifndef XML_DOM_H
#define XML_DOM_H

#include <QtGui>
#include <QtXml>
#include <QWidget>
#include <iostream>

/*!
 * \file xml_dom.h
 * \brief Gestion du fichier XML
 * \author Blanquet - Martinache
 * \version 0.1
 */

class Xml_Dom : public QWidget
{
private :
    QDomDocument dom;
    QFile xml_doc;

public:
    /*! \brief Constructeur */
    Xml_Dom();
    /*! \brief Destructeur */
    ~Xml_Dom();
    /*! \brief Recupere la valeur clavier contenue dans le XML */
    QString getKeyboard();
    /*! \brief Modifie le fichier XML pour mettre clavier à la valeur donnée (1 activé, 0 desactivé) */
    void setKeyboard(int value);
    /*! \brief Recupere la valeur longueur de pile contenue dans le XML */
    QString getPile();
    /*! \brief Modifie le fichier XML pour mettre la longueur de pile à la valeur donnée */
    void setPile(int value);
    /*! \brief Recupere la valeur bip contenue dans le XML */
    QString getBip();
    /*! \brief Modifie le fichier XML pour mettre bip à la valeur donnée (1 activé, 0 desactivé) */
    void setBip(int value);
};

#endif // XML_DOM_H
