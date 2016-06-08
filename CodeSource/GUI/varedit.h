#ifndef VAREDIT_H
#define VAREDIT_H

#include <QDialog>
#include <QStringListModel>

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


public slots:
    void afficheAtomes();
};

#endif // VAREDIT_H
