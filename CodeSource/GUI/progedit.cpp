#include "progedit.h"
#include "ui_progedit.h"

#include "../litterales/litterales.h"
#include "../manager/factory.h"

/*!
 * \file progedit.cpp
 * \brief Fenetre de modifications des programmes
 * \author Blanquet - Martinache
 * \version 0.1
 */

/*! \brief Constructeur */
progEdit::progEdit(QWidget *parent) : QDialog(parent), ui(new Ui::progEdit)
{
    ui->setupUi(this);

    this->afficheProgrammes();
    connect(ui->listeProgrammes,SIGNAL(currentTextChanged(QString)),this,SLOT(selected(QString)));
    connect(ui->valid,SIGNAL(clicked(bool)),this,SLOT(valid()));
    connect(ui->supprimer,SIGNAL(clicked(bool)),this,SLOT(suppr()));
}
/*! \brief Constructeur */
progEdit::~progEdit()
{
    delete ui;
}

/*! \brief Met a jour la liste des programmes */
void progEdit::afficheProgrammes()
{
    for (AtomeManager::Iterator it = AtomeManager::getInstance().getIterator(); !it.isDone();it.next())
    {
        QString value = QString::fromStdString(it.current().toString());
        std::string premiereLettre = it.current().getLink()->toString();
        if(premiereLettre[0]=='[')
            ui->listeProgrammes->addItem(value);
    }
}
/*! \brief Met a jour le nom et la valeur par rapport au champ selectionné */
void progEdit::selected(const QString& nom)
{
    ui->nom->setText(nom);
    std::string nomString = nom.toStdString();
    QString valeur = QString::fromStdString(AtomeManager::getInstance().getValeur(nomString)->toString());
    ui->valeur->setText(valeur);
    nomSelected=nom;
}
/*! \brief Enregistre les informations lorsque valider est pressé */
void progEdit::valid()
{


    std::string ancienNom = nomSelected.toStdString();
    std::string nouveauNom = ui->nom->text().toStdString();
    std::string nouvelleValeur = ui->valeur->toPlainText().toStdString();

    // On verifie si l'atome existe deja (modification) ou si il faut le creer
    if(AtomeManager::getInstance().getValeur(nouveauNom)==NULL)
    {
        // CREATION
        Litterale* newValue = dynamic_cast<Litterale*>(FactoryLitterale::getInstance().create(nouvelleValeur));
        AtomeManager::getInstance().addAtome(nouveauNom,newValue);
        ui->listeProgrammes->addItem(QString::fromStdString(nouveauNom));
    }
    else
    {
        // Modification
        Litterale* newValue = dynamic_cast<Litterale*>(FactoryLitterale::getInstance().create(nouvelleValeur));
        AtomeManager::getInstance().modifAtome(ancienNom,nouveauNom,newValue);
        ui->listeProgrammes->currentItem()->setText(QString::fromStdString(nouveauNom));
    }

}
/*! \brief Supprime le programme choisi */
void progEdit::suppr()
{
    std::string nom = nomSelected.toStdString();


    AtomeManager::getInstance().delAtome(nom);

    ui->listeProgrammes->currentItem()->setHidden(true);
    ui->valeur->document()->clear();
    ui->nom->clear();
}
