#include "varedit.h"
#include "ui_varedit.h"

#include "../litterales/litterales.h"
#include "../manager/factory.h"

/*!
 * \file varedit.cpp
 * \brief Fenetre de modifications des atomes
 * \author Blanquet - Martinache
 * \version 0.1
 */

/*! \brief Constructeur */
varEdit::varEdit(QWidget *parent) : QDialog(parent), ui(new Ui::varEdit)
{
    ui->setupUi(this);


    this->afficheAtomes();
    connect(ui->listeAtome,SIGNAL(currentTextChanged(QString)),this,SLOT(selected(QString)));
    connect(ui->valid,SIGNAL(clicked(bool)),this,SLOT(valid()));
    connect(ui->supprimer,SIGNAL(clicked(bool)),this,SLOT(suppr()));
}

/*! \brief Destructeur */
varEdit::~varEdit()
{
    delete ui;
}

/*! \brief Met a jour la liste des atomes */
void varEdit::afficheAtomes()
{

    for (AtomeManager::Iterator it = AtomeManager::getInstance().getIterator(); !it.isDone();it.next())
    {
        QString value = QString::fromStdString(it.current().toString());
        std::string premiereLettre = it.current().getLink()->toString();
        if(premiereLettre[0]!='[')
            ui->listeAtome->addItem(value);
    }

}

/*! \brief Met a jour le nom et la valeur par rapport au champ selectionné */
void varEdit::selected(const QString& nom)
{
    ui->nom->setText(nom);
    std::string nomString = nom.toStdString();
    QString valeur = QString::fromStdString(AtomeManager::getInstance().getValeur(nomString)->toString());
    ui->valeur->setText(valeur);
    nomSelected=nom;
}

/*! \brief Enregistre les informations lorsque valider est pressé */
void varEdit::valid()
{
    std::string ancienNom = nomSelected.toStdString();
    std::string nouveauNom = ui->nom->text().toStdString();
    std::string nouvelleValeur = ui->valeur->text().toStdString();


    // On verifie si l'atome existe deja (modification) ou si il faut le creer
    if(AtomeManager::getInstance().getValeur(nouveauNom)==NULL)
    {
        // CREATION
        Litterale* newValue = dynamic_cast<Litterale*>(FactoryLitterale::getInstance().create(nouvelleValeur));
        AtomeManager::getInstance().addAtome(nouveauNom,newValue);
        ui->listeAtome->addItem(QString::fromStdString(nouveauNom));
    }
    else
    {
        // MOdification
        Litterale* newValue = dynamic_cast<Litterale*>(FactoryLitterale::getInstance().create(nouvelleValeur));
        AtomeManager::getInstance().modifAtome(ancienNom,nouveauNom,newValue);
        ui->listeAtome->currentItem()->setText(QString::fromStdString(nouveauNom));
    }
}

/*! \brief Supprime le programme choisi */
void varEdit::suppr()
{
    std::string nom = nomSelected.toStdString();

    AtomeManager::getInstance().delAtome(nom);

    ui->listeAtome->currentItem()->setHidden(true);
    ui->valeur->clear();
    ui->nom->clear();
}
