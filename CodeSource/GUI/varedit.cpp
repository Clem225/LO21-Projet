#include "varedit.h"
#include "ui_varedit.h"

varEdit::varEdit(QWidget *parent) : QDialog(parent), ui(new Ui::varEdit)
{
    ui->setupUi(this);
}

varEdit::~varEdit()
{
    delete ui;
}
