#include "param.h"
#include "ui_param.h"

#include "../XML/xml_dom.h"

#include "mainwindow.h"

/*!
 * \file param.cpp
 * \brief Fenetre de parametres
 * \author Blanquet - Martinache
 * \version 0.1
 */

/*! \brief Constructeur */
Param::Param(QWidget *parent) : QDialog(parent), ui(new Ui::Param)
{
    ui->setupUi(this);

    // Coche/Rempli les widgets selon la valeur du XML
    keyboardUpdate();
    pileUpdate();
    bipUpdate();

    // Connects
    connect(ui->clavier,SIGNAL(toggled(bool)),this,SLOT(keyboardChecked(bool)));
    connect(ui->bip,SIGNAL(toggled(bool)),this,SLOT(bipChecked(bool)));
    connect(ui->sizePile,SIGNAL(valueChanged(int)),this,SLOT(pileChanged(int)));
}
/*! \brief Destructeur */
Param::~Param()
{
    delete ui;
}

/*! \brief Slot qui modifie le XML en fonction de la case Clavier */
void Param::keyboardChecked(bool b)
{

    if(b)
    {
        this->getXML().setKeyboard(1);
    }
    else
    {
        this->getXML().setKeyboard(0);
    }

    MainWindow::getInstance()->showKeyboard();
}
/*! \brief Recupere le XML */
Xml_Dom& Param::getXML()
{
    return paramXML;
}
/*! \brief Affiche ou non le clavier selon la valeur du XML*/
void Param::keyboardUpdate()
{
    QString v = this->getXML().getKeyboard();
    if(v=="1")
    {

        ui->clavier->setChecked(true);
    }
    else
    {

        ui->clavier->setChecked(false);
    }
}

/*! \brief Affiche la pile selon la valeur contenue dans le XML */
void Param::pileUpdate()
{
    QString v = this->getXML().getPile();
    ui->sizePile->setValue(v.toInt());

}
/*! \brief Active ou non le BIP selon la valeur du XML */
void Param::bipUpdate()
{
    QString v = this->getXML().getBip();
    if(v=="1")
    {

        ui->bip->setChecked(true);
    }
    else
    {

        ui->bip->setChecked(false);
    }

}
/*! \brief Slot qui modifie le XML en fonction de la case bip */
void Param::bipChecked(bool b)
{
    if(b)
    {
        this->getXML().setBip(1);
    }
    else
    {
        this->getXML().setBip(0);
    }
}
/*! \brief Modifie le XML en fonction de la selection de hauteur de la pile */
void Param::pileChanged(int v)
{
    this->getXML().setPile(v);
    MainWindow::getInstance()->refreshPile();
}
