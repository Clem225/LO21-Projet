#ifndef PROGEDIT_H
#define PROGEDIT_H

#include <QDialog>

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
};

#endif // PROGEDIT_H
