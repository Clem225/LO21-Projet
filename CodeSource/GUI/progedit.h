#ifndef PROGEDIT_H
#define PROGEDIT_H

#include <QDialog>

/*!
 * \file progedit.h
 * \brief Fenetre de modifications des programmes
 * \author Blanquet - Martinache
 * \version 0.1
 */

namespace Ui {
class progEdit;
}

class progEdit : public QDialog
{
    Q_OBJECT

public:
    explicit progEdit(QWidget *parent = 0);
    ~progEdit();

private:
    Ui::progEdit *ui;
    QString nomSelected;

public slots:
    /*! \brief Met a jour la liste des programmes */
    void afficheProgrammes();
    /*! \brief Met a jour le nom et la valeur par rapport au champ selectionné */
    void selected(const QString &nom);
    /*! \brief Enregistre les informations lorsque valider est pressé */
    void valid();
};

#endif // PROGEDIT_H
