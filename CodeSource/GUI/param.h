#ifndef PARAM_H
#define PARAM_H

#include <QDialog>
#include "../XML/xml_dom.h"

/*!
 * \file param.h
 * \brief Fenetre de parametres
 * \author Blanquet - Martinache
 * \version 0.1
 */

namespace Ui {
class Param;
}

class Param : public QDialog
{
    Q_OBJECT

public:
    explicit Param(QWidget *parent = 0);
    ~Param();

private:
    Ui::Param *ui;
    Xml_Dom paramXML;

public slots:
    /*! \brief Slot qui modifie le XML en fonction de la case Clavier */
    void keyboardChecked(bool b);
    /*! \brief Slot qui modifie le XML en fonction de la case bip */
    void bipChecked(bool b);
    /*! \brief Affiche ou non le clavier selon la valeur du XML*/
    void keyboardUpdate();
    /*! \brief Affiche la pile selon la valeur contenue dans le XML */
    void pileUpdate();
    /*! \brief Modifie le XML en fonction de la selection de hauteur de la pile */
    void pileChanged(int v);
    /*! \brief Active ou non le BIP selon la valeur du XML */
    void bipUpdate();
    /*! \brief Recupere le XML */
    Xml_Dom& getXML();


};

#endif // PARAM_H
