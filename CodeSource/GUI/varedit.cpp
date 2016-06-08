#include "varedit.h"
#include "ui_varedit.h"

#include "../litterales/litterales.h"

varEdit::varEdit(QWidget *parent) : QDialog(parent), ui(new Ui::varEdit)
{
    ui->setupUi(this);


    this->afficheAtomes();

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
        QString value = QString::fromStdString(it.current().getLink()->toString() + " : " +   it.current().toString());
        std::string premiereLettre = it.current().getLink()->toString();
        if(premiereLettre[0]!='[')
            ui->listeAtome->addItem(value);

    }
}
