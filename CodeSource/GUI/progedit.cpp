#include "progedit.h"
#include "ui_progedit.h"

#include "../litterales/litterales.h"

progEdit::progEdit(QWidget *parent) : QDialog(parent), ui(new Ui::progEdit)
{
    ui->setupUi(this);

    this->afficheProgrammes();
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
        QString value = QString::fromStdString(it.current().getLink()->toString() + " : " +   it.current().toString());
        std::string premiereLettre = it.current().getLink()->toString();
        if(premiereLettre[0]=='[')
            ui->listeProgrammes->addItem(value);

    }
}
