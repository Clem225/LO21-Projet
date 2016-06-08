#include "progedit.h"
#include "ui_progedit.h"

#include "../litterales/litterales.h"
#include "../manager/factory.h"

progEdit::progEdit(QWidget *parent) : QDialog(parent), ui(new Ui::progEdit)
{
    ui->setupUi(this);

    this->afficheProgrammes();
    connect(ui->listeProgrammes,SIGNAL(currentTextChanged(QString)),this,SLOT(selected(QString)));
    connect(ui->valid,SIGNAL(clicked(bool)),this,SLOT(valid()));
}

progEdit::~progEdit()
{
    delete ui;
}

// Affiche la liste des programmes
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

void progEdit::selected(const QString& nom)
{
    ui->nom->setText(nom);
    std::string nomString = nom.toStdString();
    QString valeur = QString::fromStdString(AtomeManager::getInstance().getValeur(nomString)->toString());
    ui->valeur->setText(valeur);
}

void progEdit::valid()
{
    std::string ancienNom = nomSelected.toStdString();
    std::string nouveauNom = ui->nom->text().toStdString();
    std::string nouvelleValeur = ui->valeur->toPlainText().toStdString();

    Litterale* newValue = dynamic_cast<Litterale*>(FactoryLitterale::getInstance().create(nouvelleValeur));

    AtomeManager::getInstance().modifAtome(ancienNom,nouveauNom,newValue);

    ui->listeProgrammes->currentItem()->setText(QString::fromStdString(nouveauNom));

}
