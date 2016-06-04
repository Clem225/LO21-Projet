#ifndef PARAM_H
#define PARAM_H

#include <QDialog>
#include "../XML/xml_dom.h"

namespace Ui {
class Param;
}

class Param : public QDialog
{
    Q_OBJECT

public:
    explicit Param(QWidget *parent = 0);
    ~Param();

private:
    Ui::Param *ui;
    Xml_Dom paramXML;

public slots:
    // Modifie le XML selon la case coche dans les parametres
    void keyboardChecked(bool b);
    void keyboardUpdate();
    void pileUpdate();
    Xml_Dom& getXML();


};

#endif // PARAM_H
