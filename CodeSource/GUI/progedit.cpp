#include "progedit.h"
#include "ui_progedit.h"

progEdit::progEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::progEdit)
{
    ui->setupUi(this);
}

progEdit::~progEdit()
{
    delete ui;
}
