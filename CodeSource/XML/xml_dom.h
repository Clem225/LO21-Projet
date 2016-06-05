#ifndef XML_DOM_H
#define XML_DOM_H

#include <QtGui>
#include <QtXml>
#include <QWidget>
#include <iostream>

class Xml_Dom : public QWidget
{
private :
    QDomDocument dom;
    QFile xml_doc;

public:
    Xml_Dom();
    ~Xml_Dom();
    QString getKeyboard();
    void setKeyboard(int value);
    QString getPile();
    void setPile(int value);
    QString getBip();
    void setBip(int value);
};

#endif // XML_DOM_H
