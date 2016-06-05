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
    connect(ui->clavier,SIGNAL(toggled(bool)),this,SLOT(keyboardChecked(bool)));
    connect(ui->bip,SIGNAL(toggled(bool)),this,SLOT(bipChecked(bool)));
    connect(ui->sizePile,SIGNAL(valueChanged(int)),this,SLOT(pileChanged(int)));
}

Param::~Param()
{
    delete ui;
}
// Si b = true, on affiche le clavier, sinon on le cache
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
void Param::pileUpdate()
{
    QString v = this->getXML().getPile();
    ui->sizePile->setValue(v.toInt());

}
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
void Param::pileChanged(int v)
{
    this->getXML().setPile(v);
    MainWindow::getInstance()->refreshPile();
}
