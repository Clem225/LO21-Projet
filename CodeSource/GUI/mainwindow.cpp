#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../manager/controleur.h"

#include "param.h"
#include "ui_param.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMsg("Bienvenue");


    showKeyboard();

    // Quand on appuie sur le bouton entree ou enter du clavier:
    // On vide recupere le contenu du cmdLine
    connect(ui->cmdLine,SIGNAL(returnPressed()),this,SLOT(sendCMD()));
    connect(ui->enter,SIGNAL(pressed()),this,SLOT(sendCMD()));

    // Signal mapper clavier cliquable
    QSignalMapper* signalMapper = new QSignalMapper(this);

    connect(ui->divButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->modButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->negButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->slashButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->multiplyButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->minusButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->addButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->zeroButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->oneButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->twoButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->threeButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->fourButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->fiveButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->sixButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->sevenButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->eightButton,SIGNAL(clicked()), signalMapper,SLOT(map()));
    connect(ui->nineButton,SIGNAL(clicked()), signalMapper,SLOT(map()));

    // Mapping du clavier cliquable
    signalMapper->setMapping(ui->divButton,"DIV");
    signalMapper->setMapping(ui->modButton,"MOD");
    signalMapper->setMapping(ui->negButton,"NEG");
    signalMapper->setMapping(ui->slashButton,"/");
    signalMapper->setMapping(ui->multiplyButton,"*");
    signalMapper->setMapping(ui->minusButton,"-");
    signalMapper->setMapping(ui->addButton,"+");
    signalMapper->setMapping(ui->zeroButton,"0");
    signalMapper->setMapping(ui->oneButton,"1");
    signalMapper->setMapping(ui->twoButton,"2");
    signalMapper->setMapping(ui->threeButton,"3");
    signalMapper->setMapping(ui->fourButton,"4");
    signalMapper->setMapping(ui->fiveButton,"5");
    signalMapper->setMapping(ui->sixButton,"6");
    signalMapper->setMapping(ui->sevenButton,"7");
    signalMapper->setMapping(ui->eightButton,"8");
    signalMapper->setMapping(ui->nineButton,"9");

    // Connection du mapper
    connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(addCMD(QString)));

    // Button parametre
    connect(ui->actionModifier, SIGNAL(triggered(bool)),this,SLOT(param()));

    // Button quitter
    connect(ui->actionQuitter,SIGNAL(triggered(bool)),this,SLOT(close()));



}

MainWindow::~MainWindow()
{
    delete ui;
}
// Rafraichit l'affichage de la pile
void MainWindow::refreshPile()
{
    QString pile = QString::fromStdString(Controleur::getInstance().pileString());
    ui->pileMsg->setText(pile);

}
// Execute la commande indiqué dans la barre de commande
void MainWindow::sendCMD()
{
    QString cmd = ui->cmdLine->text();
    ui->cmdLine->clear();
    std::string cmdStr = cmd.toStdString();

    Controleur::getInstance().commande(cmdStr);
    this->refreshPile();

}
// Change le texte utilisateur
void MainWindow::setMsg(QString msg)
{
   ui->msgLine->setText(msg);

}

// Ajoute cmd à la barre de commande
void MainWindow::addCMD(QString cmd)
{

    ui->cmdLine->insert(cmd);

}

// Initialisation de l'attribut statique
MainWindow::Handler MainWindow::handler = MainWindow::Handler();

// Singleton
MainWindow* MainWindow::getInstance()
{
    if(handler.instance==nullptr) {
    handler.instance=new MainWindow;
}
return handler.instance;
}


void MainWindow::param()
{
    Param param(this);
    param.exec();
}

void MainWindow::showKeyboard()
{

    int value = paramXML.getKeyboard().toInt();

    if(value==1)
    {

        ui->divButton->show();
        ui->modButton->show();
        ui->negButton->show();
        ui->slashButton->show();
        ui->multiplyButton->show();
        ui->minusButton->show();
        ui->addButton->show();
        ui->zeroButton->show();
        ui->oneButton->show();
        ui->twoButton->show();
        ui->threeButton->show();
        ui->fourButton->show();
        ui->fiveButton->show();
        ui->sixButton->show();
        ui->sevenButton->show();
        ui->eightButton->show();
        ui->nineButton->show();
    }
    else
    {
        ui->divButton->hide();
        ui->modButton->hide();
        ui->negButton->hide();
        ui->slashButton->hide();
        ui->multiplyButton->hide();
        ui->minusButton->hide();
        ui->addButton->hide();
        ui->zeroButton->hide();
        ui->oneButton->hide();
        ui->twoButton->hide();
        ui->threeButton->hide();
        ui->fourButton->hide();
        ui->fiveButton->hide();
        ui->sixButton->hide();
        ui->sevenButton->hide();
        ui->eightButton->hide();
        ui->nineButton->hide();
    }

}
void MainWindow::showKeyboard(bool b)
{


    if(b)
    {

        ui->divButton->show();
        ui->modButton->show();
        ui->negButton->show();
        ui->slashButton->show();
        ui->multiplyButton->show();
        ui->minusButton->show();
        ui->addButton->show();
        ui->zeroButton->show();
        ui->oneButton->show();
        ui->twoButton->show();
        ui->threeButton->show();
        ui->fourButton->show();
        ui->fiveButton->show();
        ui->sixButton->show();
        ui->sevenButton->show();
        ui->eightButton->show();
        ui->nineButton->show();
    }
    else
    {
        ui->divButton->hide();
        ui->modButton->hide();
        ui->negButton->hide();
        ui->slashButton->hide();
        ui->multiplyButton->hide();
        ui->minusButton->hide();
        ui->addButton->hide();
        ui->zeroButton->hide();
        ui->oneButton->hide();
        ui->twoButton->hide();
        ui->threeButton->hide();
        ui->fourButton->hide();
        ui->fiveButton->hide();
        ui->sixButton->hide();
        ui->sevenButton->hide();
        ui->eightButton->hide();
        ui->nineButton->hide();
    }

}
