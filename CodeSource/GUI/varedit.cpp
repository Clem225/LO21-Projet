#include "varedit.h"
#include "ui_varedit.h"

#include "../litterales/litterales.h"
#include "../manager/factory.h"

// Constructeur
varEdit::varEdit(QWidget *parent) : QDialog(parent), ui(new Ui::varEdit)
{
    ui->setupUi(this);


    this->afficheAtomes();
    connect(ui->listeAtome,SIGNAL(currentTextChanged(QString)),this,SLOT(selected(QString)));
    connect(ui->valid,SIGNAL(clicked(bool)),this,SLOT(valid()));
}

varEdit::~varEdit()
{
    delete ui;
}

// Affiche la liste des atomes
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

void varEdit::selected(const QString& nom)
{
    ui->nom->setText(nom);
    std::string nomString = nom.toStdString();
    QString valeur = QString::fromStdString(AtomeManager::getInstance().getValeur(nomString)->toString());
    ui->valeur->setText(valeur);
    nomSelected=nom;
}
void varEdit::valid()
{
    std::string ancienNom = nomSelected.toStdString();
    std::string nouveauNom = ui->nom->text().toStdString();
    std::string nouvelleValeur = ui->valeur->text().toStdString();

    Litterale* newValue = dynamic_cast<Litterale*>(FactoryLitterale::getInstance().create(nouvelleValeur));

    AtomeManager::getInstance().modifAtome(ancienNom,nouveauNom,newValue);

    ui->listeAtome->currentItem()->setText(QString::fromStdString(nouveauNom));
}
