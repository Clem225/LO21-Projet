#ifndef VAREDIT_H
#define VAREDIT_H

#include <QDialog>

namespace Ui {
class varEdit;
}

class varEdit : public QDialog
{
    Q_OBJECT

public:
    explicit varEdit(QWidget *parent = 0);
    ~varEdit();

private:
    Ui::varEdit *ui;
    QString nomSelected;


public slots:
    void afficheAtomes();
    void selected(const QString &nom);
    void valid();
};

#endif // VAREDIT_H
