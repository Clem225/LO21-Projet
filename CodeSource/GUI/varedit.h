#ifndef VAREDIT_H
#define VAREDIT_H

#include <QDialog>

/*!
 * \file varedit.h
 * \brief Fenetre de modifications des atomes
 * \author Blanquet - Martinache
 * \version 0.1
 */

namespace Ui {
class varEdit;
}

class varEdit : public QDialog
{
    Q_OBJECT

public:
    /*! \brief Constructeur */
    explicit varEdit(QWidget *parent = 0);
    /*! \brief Destructeur */
    ~varEdit();

private:
    Ui::varEdit *ui;
    QString nomSelected;

public slots:
    /*! \brief Met a jour la liste des atomes */
    void afficheAtomes();
    /*! \brief Met a jour le nom et la valeur par rapport au champ selectionné */
    void selected(const QString &nom);
    /*! \brief Enregistre les informations lorsque valider est pressé */
    void valid();
    /*! \brief Supprime le programme choisi */
    void suppr();
};

#endif // VAREDIT_H
