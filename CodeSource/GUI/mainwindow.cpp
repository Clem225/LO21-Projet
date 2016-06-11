#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../manager/controleur.h"

#include "param.h"
#include "ui_param.h"

#include "progedit.h"
#include "varedit.h"

#include <fstream>
#include <QMessageBox>
#include <limits.h>

#include <QShortcut>

bool hasLoaded=false;

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

    // Button atome
    connect(ui->actionAtomes, SIGNAL(triggered(bool)),this,SLOT(atomes()));
    connect(ui->actionProgrammes, SIGNAL(triggered(bool)),this,SLOT(programmes()));


    // Button undo/redo
    connect(ui->actionUndo, SIGNAL(triggered(bool)),this,SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered(bool)),this,SLOT(redo()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(undo()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this, SLOT(redo()));

    // Button quitter
    connect(ui->actionQuitter,SIGNAL(triggered(bool)),this,SLOT(close()));


    if(!hasLoaded)
    {
        hasLoaded=true;
        std::ifstream ifsPile("dataPile.dat");
        std::string line;
        std::stack<std::string> pileTampon;
        while(getline (ifsPile,line))
        {
              pileTampon.push(line);
        }
        if (ifsPile.is_open())
        {
        ifsPile.close();
        }

        while(!pileTampon.empty())
        {
            Controleur::getInstance().commande(pileTampon.top());
            pileTampon.pop();
        }
        std::ifstream ifsAtom("dataAtome.dat");
        if (ifsAtom.is_open())
        {
            std::string line;
            while(getline (ifsAtom,line))
            {
                  Controleur::getInstance().commande(line);
            }
                ifsAtom.close();
        }
            this->refreshPile();
    }

}
// Surcharge de closeEvent pour sauvegarder la pile et les atomes à la sortie + pour supprimer les singletons
void MainWindow::closeEvent(QCloseEvent *event)
 {
    // On sauvergarde la pile
    std::ofstream ofsPile("dataPile.dat");
     if (ofsPile.good())
     {
        ofsPile<<Controleur::getInstance().pileString(INT_MAX);
        ofsPile.close();
     }
     else
     {
         QMessageBox::information(this, "Sauvegarde", "Une erreur est survenue lors de la sauvegarde") ;
         ofsPile.close();
         event->accept();

     }

     // On sauvegarde les atomes
     std::ofstream ofsAtom("dataAtome.dat");
     if (ofsAtom.good())
     {
          //On cherche ce nom d'atome dans AtomeManager grace à un iterator
          for (AtomeManager::Iterator it = AtomeManager::getInstance().getIterator(); !it.isDone();it.next())
          {
            ofsAtom<< it.current().getLink()->toString()<< " " <<   it.current().toString()<<" STO\n";
          }
          ofsAtom.close();


      }
     else
     {
          QMessageBox::information(this, "Sauvegarde", "Une erreur est survenue lors de la sauvegarde") ;
          ofsAtom.close();
          event->accept();
      }



     // On ferme les factorys et autres singletons
     FactoryLitterale::libererInstance();
     FactoryOperateur::libererInstance();
     Controleur::libererInstance();
     AtomeManager::libererInstance();

     // On ferme la fenetre
     event->accept();

 }

MainWindow::~MainWindow()
{
    delete ui;
}

// Rafraichit l'affichage de la pile
void MainWindow::refreshPile()
{
    ui->pileMsg->clear();
    int value = paramXML.getPile().toInt();
    QString pile = QString::fromStdString(Controleur::getInstance().pileString(value));
    ui->pileMsg->setText(pile);

}

// Execute la commande indiqué dans la barre de commande
void MainWindow::doBip()
{
    int value = paramXML.getBip().toInt();
    if(value==1)
        QApplication::beep();

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
   this->doBip();

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

// Lance la fenetre param
void MainWindow::param()
{
    Param param(this);
    param.exec();
}

// Lance la fenetre atome
void MainWindow::atomes()
{
    varEdit edit(this);
    edit.exec();
}

// Lance la fenetre programme
void MainWindow::programmes()
{
    progEdit edit(this);
    edit.exec();
}

// Cache ou affiche le clavier selon la valeur dans le XML
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

void MainWindow::undo()
{
    Controleur::getInstance().undo();
}
void MainWindow::redo()
{
    Controleur::getInstance().redo();
}
