#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../manager/controleur.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Quand on appuie sur le bouton entree :
    // On vide recupere le contenu du cmdLine
    connect(ui->cmdLine,SIGNAL(returnPressed()),this,SLOT(sendCMD()));

    connect(ui->enter,SIGNAL(pressed()),this,SLOT(sendCMD()));

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

    connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(addCMD(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    QString pile = QString::fromStdString(Controleur::getInstance().pileString());
    ui->pileMsg->setText(pile);

}

void MainWindow::sendCMD()
{
    QString cmd = ui->cmdLine->text();
    ui->cmdLine->clear();
    std::string cmdStr = cmd.toStdString();

    Controleur::getInstance().commande(cmdStr);
    this->refresh();

}

void MainWindow::addCMD(QString cmd)
{

    ui->cmdLine->insert(cmd);

}
