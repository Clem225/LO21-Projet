#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../manager/controleur.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Quand on appuie sur le bouton entree :
    // On vide recupere le contenu du cmdLine
    connect(ui->cmdLine,SIGNAL(returnPressed()),this,SLOT(sendCMD()));

    //connect(ui->enter,SIGNAL(pressed()),this,SLOT(refresh()));
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
