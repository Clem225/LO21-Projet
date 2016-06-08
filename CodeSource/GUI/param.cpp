#include "param.h"
#include "ui_param.h"
#include "../XML/xml_dom.h"
#include "mainwindow.h"
#include <unistd.h>
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

Param::~Param()
{
    delete ui;
}

// Si b = true, change le XML en vrai, sinon en faux. Ensuite on raffraichit l'affichage du clavier
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

Xml_Dom& Param::getXML()
{
    return paramXML;
}
// Coche le widget en fonction du contenu du XML
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

// Change la valeur en fonction de ce qui est contenu dans le XML
void Param::pileUpdate()
{
    QString v = this->getXML().getPile();
    ui->sizePile->setValue(v.toInt());

}
// Change la valeur en fonction de ce qui est contenu dans le XML
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
// Change la valeur du BIP dans le XML
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
// Change la valeur de taille de pile dans le XML puis actualise l'affichage
void Param::pileChanged(int v)
{
    this->getXML().setPile(v);
    MainWindow::getInstance()->refreshPile();
}
