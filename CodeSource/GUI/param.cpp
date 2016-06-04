#include "param.h"
#include "ui_param.h"
#include "../XML/xml_dom.h"
#include "mainwindow.h"
#include <unistd.h>
Param::Param(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Param)
{
    ui->setupUi(this);



    keyboardUpdate();
    connect(ui->clavier,SIGNAL(toggled(bool)),this,SLOT(keyboardChecked(bool)));

}

Param::~Param()
{
    delete ui;
}

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

    MainWindow::getInstance()->showKeyboard(b);
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
